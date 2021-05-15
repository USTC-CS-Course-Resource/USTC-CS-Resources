#include "mpi.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include <math.h>
#include <unistd.h>
#include <chrono>

using namespace std;
using namespace chrono;

int _ = 0;

int main(int argc, char* argv[]) {
    // init MPI
    int group_size, my_rank;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &group_size);

    auto psrs_time_begin = chrono::system_clock::now();

    // data size
    int n = 10000000;
    int step = (int)(ceil((double)n / group_size));
    int my_n = step;
    if (my_rank == group_size - 1) my_n = n - my_rank * step;

    // generate data
    srand(my_rank * group_size);
    auto my_array = new int[my_n];
    for (int i = 0; i < my_n; i++) {
        my_array[i] = rand() % (n - 0) + 0;
    }

    /************ begin ***********/
    if (my_rank == 0) psrs_time_begin = chrono::system_clock::now();
    // local sort
    sort(my_array, my_array + my_n);
#ifdef DEBUG
    printf("data in process %d:\t", my_rank);
    for (int i = 0; i < my_n; i++) {
        printf("%d ", my_array[i]);
    }
    printf("\n");
#endif

    // prepare for sampling
    int my_sample_step = my_n / group_size;
    auto my_samples = new int[group_size] {0};
    auto num_all_samples = group_size * group_size;

    int* all_samples;
    if (my_rank == 0) all_samples = new int[num_all_samples];

    // sample
    for (int i = 0; i < group_size; i++) {
        my_samples[i] = my_array[i * my_sample_step];
    }
    
    // gather and sort samples, then pick pivots
    MPI_Gather(my_samples, group_size, MPI_INT,
        all_samples, group_size, MPI_INT, 0, MPI_COMM_WORLD);

    int num_pivots = group_size - 1;
    auto pivots = new int[num_pivots];
    if (my_rank == 0) {
        sort(all_samples, all_samples + num_all_samples);
        for (int i = 0; i < num_pivots; i++) {
            pivots[i] = all_samples[group_size * (i + 1)];
        }
    }

    // broadcast pivots
    MPI_Bcast(pivots, num_pivots, MPI_INT, 0, MPI_COMM_WORLD);

#ifdef DEBUG
    if(my_rank == 0) {
        printf("process %d recv pivots: \"", my_rank);
        for (int i = 0; i < num_pivots; i++) {
            printf("%d ", pivots[i]);
        }
        printf("\"\n");
    }
#endif

    //================================ global swapping ====================================//

    auto my_swapped_array = new int[n];
    auto my_swapped_seg_sizes = new int[group_size] {0};
    auto my_seg_idx = new int[group_size + 1] {0};
    auto requests = new MPI_Request[group_size];
    {
        /// prepare for sending
        int k = 0;
        for (int j = 0; j < my_n && k < group_size - 1; j++) {
            // maybe no elements between some pivots
            while (my_array[j] > pivots[k] && k < group_size - 1) {
                my_seg_idx[++k] = j;
            }
        }
        //// maybe all less than pivots
        while (k < group_size) {
            my_seg_idx[++k] = my_n;
        }
    }
    /// recv
    for (int i = 0; i < group_size; i++) {
        MPI_Irecv(my_swapped_seg_sizes + i, 1, MPI_INT, i, /*tag=*/0, MPI_COMM_WORLD, requests + i);
    }
    auto seg_sizes = new int[group_size] {0};
    for (int i = 0; i < group_size; i++) {
        seg_sizes[i] = my_seg_idx[i+1] - my_seg_idx[i];
    }
    /// send
    for (int i = 0; i < group_size; i++) {
        MPI_Send(seg_sizes + i, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
    }

    MPI_Waitall(group_size, requests, MPI_STATUS_IGNORE);

    auto my_swapped_seg_idx = new int[group_size + 1];
    auto tmp_seg_idx = new int[group_size + 1];
    for (int i = 0; i <= group_size; i++) {
        if (i > 0) {
            my_swapped_seg_idx[i] = my_swapped_seg_idx[i - 1] + my_swapped_seg_sizes[i - 1];
            tmp_seg_idx[i] = my_swapped_seg_idx[i];
        }
    }

    for (int i = 0; i < group_size; i++) {
        MPI_Irecv(my_swapped_array + my_swapped_seg_idx[i], my_swapped_seg_sizes[i], MPI_INT, i, /*tag=*/1, MPI_COMM_WORLD, requests + i);
    }

    for (int i = 0; i < group_size; i++) {
        MPI_Send(my_array + my_seg_idx[i], seg_sizes[i], MPI_INT, i, /*tag=*/1, MPI_COMM_WORLD);
    }
    MPI_Waitall(group_size, requests, MPI_STATUS_IGNORE);

    if (my_rank == 0) {
        auto psrs_time_end = chrono::system_clock::now();
        auto psrs_sort_duration = chrono::duration_cast<chrono::nanoseconds>(psrs_time_end - psrs_time_begin);
        printf("before local merge:\t %ld ns\n", psrs_sort_duration.count());
    }

    //================================ local merge ====================================//
    auto my_result = new int[n];
    using value_array_idx_pair = pair<int, int>;
    auto cmp = [](const value_array_idx_pair &a, const value_array_idx_pair &b) { return (a.first) > (b.first); };
    priority_queue<value_array_idx_pair, vector<value_array_idx_pair>, decltype(cmp)> min_heap(cmp);

    for (int i = 0; i < group_size; i++) {
        min_heap.push({my_swapped_array[tmp_seg_idx[i]++], i});
    }

    int idx = 0;
    while (!min_heap.empty()) {
        auto min_pair = min_heap.top();
        min_heap.pop();
        if (tmp_seg_idx[min_pair.second] < my_swapped_seg_idx[min_pair.second+1]) {
            min_heap.push({my_swapped_array[tmp_seg_idx[min_pair.second]++], min_pair.second});
        }
        my_result[idx++] = min_pair.first;
    }

    if (my_rank == 0) {
        auto psrs_time_end = chrono::system_clock::now();
        auto psrs_sort_duration = chrono::duration_cast<chrono::nanoseconds>(psrs_time_end - psrs_time_begin);
        printf("before gather all result:\t %ld ns\n", psrs_sort_duration.count());
    }

    //================================ gather all result ====================================//
    // gather size
    auto all_result_begins = new int[group_size] {0};
    auto all_result_sizes = new int[group_size];
    if (my_rank == 0) {
        for (int i = 0; i < group_size; i++) {
            MPI_Irecv(all_result_sizes + i, /*count=*/1, MPI_INT, i, /*tag=*/0, MPI_COMM_WORLD, requests + i);
        }
    }
    MPI_Send(&my_swapped_seg_idx[group_size], /*count=*/1, MPI_INT, /*dest=*/0, /*tag=*/0, MPI_COMM_WORLD);
    if (my_rank == 0) {
        MPI_Waitall(group_size, requests, MPI_STATUS_IGNORE);
        for (int i = 0; i < group_size; i++) {
            if (i > 0) {
                all_result_begins[i] = all_result_begins[i - 1] + all_result_sizes[i - 1];
            }
        }
    }

    // gather final result
    auto all_results = new int[n] {0};
    if (my_rank == 0) {
        for (int i = 0; i < group_size; i++) {
            MPI_Irecv(all_results + all_result_begins[i], /*count=*/all_result_sizes[i], MPI_INT, i, /*tag=*/0, MPI_COMM_WORLD, requests + i);
        }
    }
    MPI_Send(my_result, /*count=*/my_swapped_seg_idx[group_size], MPI_INT, /*dest=*/0, /*tag=*/0, MPI_COMM_WORLD);
    if (my_rank == 0) {
        MPI_Waitall(group_size, requests, MPI_STATUS_IGNORE);
        auto psrs_time_end = chrono::system_clock::now();
        auto psrs_sort_duration = chrono::duration_cast<chrono::nanoseconds>(psrs_time_end - psrs_time_begin);
#ifdef DEBUG        
        sleep(1);
        for (int i = 0; i < n; i++) {
            printf("%d ", all_results[i]);
        }
        printf("\n");
#endif
        printf("=====================Summary=======================\n");
        // if (memcmp(correct_answer, result_array, sizeof(int) * n) == 0) {
        //     printf("\033[1;32mThe result is correct!\033[0m\n");
        // }
        // else {
        //     printf("\033[1;31mThe result is wrong!\033[0m\n");
        // }
        // printf("Quick Sort:\t %ld ns\n", qsort_duration.count());
        printf("PSRS Sort:\t %ld ns\n", psrs_sort_duration.count());
        // printf("speedup:\t %lf\n", qsort_duration.count() / (double)psrs_sort_duration.count());
        printf("===================================================\n");
    }
    

    /************  end  ***********/
    MPI_Finalize();
}

