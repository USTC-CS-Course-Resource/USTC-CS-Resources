#include "mpi.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include <math.h>
#include <unistd.h>
#include <chrono>
#include <cstring>

using namespace std;
using namespace chrono;

inline int* size_to_idx(int n, int* sizes) {
    auto idx = new int[n+1] {0};
    for (int i = 1; i <= n; i++) {
        idx[i] = idx[i-1] + sizes[i-1];
    }
    return idx;
}

inline int* idx_to_size(int n, int* idx) {
    auto size = new int[n] {0};
    for (int i = 0; i < n; i++) {
        size[i] = idx[i+1] - idx[i];
    }
    return size;
}

int main(int argc, char* argv[]) {
    // gernerate data
    int n = 1e8;
    auto raw_array = new int[n];
    srand(0);
    for (int i = 0; i < n; i++) {
        raw_array[i] = rand() % (n - 0) + 0;
    }

#ifndef PSRS_ONLY
    /*======================== std::sort begin ========================*/
    auto correct_answer = new int[n];
    memcpy(correct_answer, raw_array, sizeof(int) * n);
    auto qsort_time_begin = chrono::system_clock::now();
    sort(correct_answer, correct_answer + n);
    auto qsort_time_end = chrono::system_clock::now();
    auto qsort_duration = chrono::duration_cast<chrono::nanoseconds>(qsort_time_end - qsort_time_begin);
    /*======================== std::sort end ========================*/
#endif


    /*======================== PSRS begin ========================*/
    // init MPI
    int group_size, my_rank;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &group_size);
    std::chrono::_V2::system_clock::time_point psrs_time_begin;
    if (my_rank == 0) psrs_time_begin = chrono::system_clock::now();

    // set data size
    int step = (int)(ceil((double)n / group_size));
    int my_n = step;
    if (my_rank == group_size - 1) my_n = n - my_rank * step;
    auto sizes = new int[group_size];
    for (int i = 0; i < group_size; i++) {
        sizes[i] = step;
    }
    sizes[group_size-1] = n - (group_size - 1) * step;

    // scatter data
    auto my_array = new int[my_n];
    MPI_Scatterv(raw_array, sizes, size_to_idx(group_size, sizes), MPI_INT, my_array, my_n, MPI_INT, 0, MPI_COMM_WORLD);
    delete raw_array;

#ifdef PROFILE
    if (my_rank == 0) printf("after scattered data:\t %ld ns\n", chrono::duration_cast<chrono::nanoseconds>(chrono::system_clock::now() - psrs_time_begin).count());
#endif
    // local sort
    sort(my_array, my_array + my_n);
#ifdef DEBUG
    printf("data in process %d:\t", my_rank);
    for (int i = 0; i < my_n; i++) {
        printf("%d ", my_array[i]);
    }
    printf("\n");
#endif
#ifdef PROFILE
    if (my_rank == 0) printf("after local sort:\t %ld ns\n", chrono::duration_cast<chrono::nanoseconds>(chrono::system_clock::now() - psrs_time_begin).count());
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
    MPI_Gather(my_samples, group_size, MPI_INT, all_samples, group_size, MPI_INT, 0, MPI_COMM_WORLD);

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
        printf("pivots: \"");
        for (int i = 0; i < num_pivots; i++) {
            printf("%d ", pivots[i]);
        }
        printf("\"\n");
    }
#endif

#ifdef PROFILE
    if (my_rank == 0) printf("after broadcast pivots:\t %ld ns\n", chrono::duration_cast<chrono::nanoseconds>(chrono::system_clock::now() - psrs_time_begin).count());
#endif

    //================================ global swapping ====================================//
    auto my_swapped_seg_sizes = new int[group_size] {0};
    auto my_seg_idx = new int[group_size + 1] {0};
    auto requests = new MPI_Request[group_size];
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
    auto my_seg_sizes = idx_to_size(group_size, my_seg_idx);

    // scatter the sizes
    for (int i = 0; i < group_size; i++) {
        // scatter my sizes to each according process
        MPI_Iscatter(my_seg_sizes, 1, MPI_INT, &my_swapped_seg_sizes[i], 1, MPI_INT, i, MPI_COMM_WORLD, &requests[i]);
    }
    MPI_Waitall(group_size, requests, MPI_STATUS_IGNORE);

    // compute the `my_swapped_seg_idx`
    auto my_swapped_seg_idx = size_to_idx(group_size, my_swapped_seg_sizes);
    auto my_swapped_n = my_swapped_seg_idx[group_size];

#if defined DEBUG && defined VERBOSE
    printf("p%d swapped sizes:\t", my_rank);
    for (int i = 0; i < group_size; i++) {
        printf("%d ", my_swapped_seg_sizes[i]);
    }
    printf("\n");

    printf("p%d swapped idxes:\t", my_rank);
    for (int i = 0; i <= group_size; i++) {
        printf("%d ", my_swapped_seg_idx[i]);
    }
    printf("\n");
#endif

    // Gather data
    auto my_swapped_array = new int[my_swapped_n];
    for (int i = 0; i < group_size; i++) {
        MPI_Igatherv(&my_array[my_seg_idx[i]], my_seg_sizes[i], MPI_INT, 
            /*recvbuf=*/my_swapped_array, /*recvcounts=*/my_swapped_seg_sizes, /*displs=*/my_swapped_seg_idx, MPI_INT, 
            /*root=*/i, MPI_COMM_WORLD, &requests[i]);
    }
    MPI_Waitall(group_size, requests, MPI_STATUS_IGNORE);

#ifdef PROFILE
    if (my_rank == 0) printf("after global swapping:\t %ld ns\n", chrono::duration_cast<chrono::nanoseconds>(chrono::system_clock::now() - psrs_time_begin).count());
#endif

#ifdef DEBUG
    printf("p%d swapped array:\t", my_rank);
    for (int i = 0; i < my_swapped_n; i++) {
        printf("%d ", my_swapped_array[i]);
    }
    printf("\n");
#endif

    //================================ local merge ====================================//
    auto tmp_seg_idx = new int[group_size + 1] {0};
    memcpy(tmp_seg_idx, my_swapped_seg_idx, sizeof(int) * (group_size + 1));
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

#ifdef PROFILE
    if (my_rank == 0) printf("after local merge:\t %ld ns\n", chrono::duration_cast<chrono::nanoseconds>(chrono::system_clock::now() - psrs_time_begin).count());
#endif

#ifdef DEBUG
    printf("p%d local merged array:\t", my_rank);
    for (int i = 0; i < my_swapped_n; i++) {
        printf("%d ", my_result[i]);
    }
    printf("\n");
#endif

    //================================ gather all result ====================================//
    // gather size
    auto result_idx = new int[group_size + 1] {0};
    auto result_sizes = new int[group_size] {0};
    MPI_Gather(&my_swapped_n, 1, MPI_INT, result_sizes, 1, MPI_INT, /*root=*/0, MPI_COMM_WORLD);

    if (my_rank == 0) {
        for (int i = 1; i <= group_size; i++) {
            result_idx[i] = result_idx[i - 1] + result_sizes[i - 1];
        }
    }

    auto result = new int[n];
    MPI_Gatherv(my_result, my_swapped_n, MPI_INT, result, result_sizes, result_idx, MPI_INT, 0, MPI_COMM_WORLD);
    
#ifdef PROFILE
    if (my_rank == 0) printf("after gather  results:\t %ld ns\n", chrono::duration_cast<chrono::nanoseconds>(chrono::system_clock::now() - psrs_time_begin).count());
#endif

    if (my_rank == 0) {
        MPI_Waitall(group_size, requests, MPI_STATUS_IGNORE);
        auto psrs_time_end = chrono::system_clock::now();
        auto psrs_sort_duration = chrono::duration_cast<chrono::nanoseconds>(psrs_time_end - psrs_time_begin);
#ifdef DEBUG        
        sleep(1);
        printf("result sizes:\t");
        for (int i = 0; i < group_size; i++) {
            printf("%d ", result_sizes[i]);
        }
        printf("\n");
        printf("gathered result:\t");
        for (int i = 0; i < n; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
#endif
        printf("=====================Summary=======================\n");
#ifndef PSRS_ONLY
        if (memcmp(correct_answer, result, sizeof(int) * n) == 0) {
            printf("\033[1;32mThe result is correct!\033[0m\n");
        }
        else {
            printf("\033[1;31mThe result is wrong!\033[0m\n");
        }
        printf("Quick Sort:\t %ld ns\n", qsort_duration.count());
#endif
        printf("PSRS Sort:\t %ld ns\n", psrs_sort_duration.count());
#ifndef PSRS_ONLY
        printf("speedup:\t %lf\n", qsort_duration.count() / (double)psrs_sort_duration.count());
#endif
        printf("===================================================\n");
    }
    
    delete my_array;
    delete my_seg_idx;
    delete my_seg_sizes;
    delete my_swapped_array;
    delete my_swapped_seg_idx;
    delete my_swapped_seg_sizes;

    /************  end  ***********/
    MPI_Finalize();
}

