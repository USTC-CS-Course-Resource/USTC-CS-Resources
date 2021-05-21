#include <iostream>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <queue>
#include <cstring>
#include <chrono>
#include <cstdlib>
#include <omp.h>

#define NUM_THREADS 4

using namespace std;

int main()
{
    int n = 1e6;
    srand(0);
    auto array = new int[n];
#ifndef ONLY_PSRS
    auto correct_answer = new int[n];
#endif
    for (int i = 0; i < n; i++) {
        int tmp = rand() % (n - 0) + 0;
        array[i] = tmp;
#ifndef ONLY_PSRS
        correct_answer[i] = tmp;
#endif
    }

#ifndef ONLY_PSRS
    // begin timing for quick sort
    auto qsort_time_begin = chrono::system_clock::now();
    sort(correct_answer, correct_answer + n);
    auto qsort_time_end = chrono::system_clock::now();
    auto qsort_duration = chrono::duration_cast<chrono::nanoseconds>(qsort_time_end - qsort_time_begin);
    // end timing for quicksort
#endif
    // begin timing for psrs sort
    auto psrs_time_begin = chrono::system_clock::now();
    // size of divided array
    int step = ceil((double)n / NUM_THREADS);

	omp_set_num_threads(NUM_THREADS);

    int samples[NUM_THREADS * NUM_THREADS] = {0};

#ifdef PROFILE
    auto time_begin = chrono::system_clock::now();
#endif
#pragma omp parallel 
{
	int i = omp_get_thread_num();
    // local sort
    int begin = i * step;
    int end = min(begin + step , n);
    int local_n = end - begin;
    sort(array + begin, array + end);
    // sample
    // TODO: haven't implement when `the size of last segment is less than n / p`
    assert(end - begin > NUM_THREADS && "haven't implement when `the size of last segment is less than NUM_THREADS`");
    int sample_step = local_n / NUM_THREADS;
    int samples_begin = i * NUM_THREADS;
    int samples_end = min(samples_begin + NUM_THREADS , NUM_THREADS * NUM_THREADS);;
    for (int j = samples_begin, A_idx = begin; j < samples_end; j += 1, A_idx += sample_step) {
        samples[j] = array[A_idx];
    }
}
#ifdef PROFILE
    printf("sample:    \t%ld ns\n", chrono::duration_cast<chrono::nanoseconds>(chrono::system_clock::now() - time_begin).count());
    time_begin = chrono::system_clock::now();
#endif


#ifdef DEBUG
    printf("local sort:\n");
    for (int i = 0; i < n; i++) {
        if (i % step == 0) printf("| ");
        printf("%d ", array[i]);
    }
    printf("|\n");

    printf("sample:\n");
    for (int i = 0; i < NUM_THREADS * NUM_THREADS; i++) {
        if (i % NUM_THREADS == 0) printf("| ");
        printf("%d ", samples[i]);
    }
    printf("|\n");
#endif
    // sort samples
    sort(samples, std::end(samples));

#ifdef DEBUG
    printf("sorted sample:\n");
    for (int i = 0; i < NUM_THREADS * NUM_THREADS; i++) {
        printf("%d ", samples[i]);
    }
    printf("\n");
#endif

    // pick pivots
    int pivots[NUM_THREADS - 1];
    for (int i = 0, sample_idx = NUM_THREADS; i < NUM_THREADS - 1; i++, sample_idx += NUM_THREADS) {
        pivots[i] = samples[sample_idx];
    }
#ifdef DEBUG
    printf("pivots:\n");
    for (int i = 0; i < NUM_THREADS - 1; i++) {
        printf("%d ", pivots[i]);
    }
    printf("\n");
#endif

    // // get segments' index for global swapping
    int seg_idx[NUM_THREADS][NUM_THREADS + 1] = {0};
#pragma omp parallel
{
    int i = omp_get_thread_num();
    int begin = i * step;
    int end = min(begin + step , n);
    int k = 0;
    seg_idx[i][0] = begin;
    for (int j = begin; j < end && k < NUM_THREADS - 1; j++) {
        // maybe no elements between some pivots
        while (array[j] > pivots[k] && k < NUM_THREADS - 1) {
            seg_idx[i][++k] = j;
        }
    }
    // maybe all less than pivots
    while (k < NUM_THREADS) {
        seg_idx[i][++k] = end;
    }
}
#if defined DEBUG && defined VERBOSE
    printf("seg_idx:\n");
    for (int i = 0; i < NUM_THREADS; i++) {
        for (int j = 0; j <= NUM_THREADS; j++) {
            printf("%d ", seg_idx[i][j]);
        }
        printf("\n");
    }
#endif

    // get swapped local size and local end and do swap
    int swapped_local_n[NUM_THREADS] = {0};
    int swapped_local_begin[NUM_THREADS + 1] = {0};
#pragma omp parallel
{
    int i = omp_get_thread_num();
    for (int j = 0; j < NUM_THREADS; j++) {
        swapped_local_n[i] += seg_idx[j][i+1] - seg_idx[j][i];
    }
}
    for (int j = 1; j <= NUM_THREADS; j++) {
        swapped_local_begin[j] = swapped_local_begin[j-1] + swapped_local_n[j-1];
    }

#if defined DEBUG && defined VERBOSE
    printf("swapped_local_n:\n");
    for (int i = 0; i < NUM_THREADS; i++) {
        printf("%d ", swapped_local_n[i]);
    }
    printf("\n");
    printf("swapped_local_begin:\n");
    for (int i = 0; i < NUM_THREADS; i++) {
        printf("%d ", swapped_local_begin[i]);
    }
    printf("\n");
#endif
#ifdef PROFILE
    printf("prepare for swap:    \t%ld ns\n", chrono::duration_cast<chrono::nanoseconds>(chrono::system_clock::now() - time_begin).count());
    time_begin = chrono::system_clock::now();
#endif
    // do swap and local merge sort
    // auto begin_time = chrono::system_clock::now();
    auto swapped_array = new int[n];
    auto result_array = new int[n];
#pragma omp parallel
{
    int i = omp_get_thread_num();
    int idx = swapped_local_begin[i];
    int local_seg_end[NUM_THREADS] = {0};
    int local_seg_idx[NUM_THREADS] = {0};
    for (int j = 0; j < NUM_THREADS; j++) {
        local_seg_idx[j] = idx;
        auto local_seg_size = seg_idx[j][i+1] - seg_idx[j][i];
        memcpy(swapped_array + idx, array + seg_idx[j][i], local_seg_size * sizeof(int));
        idx += local_seg_size;
        local_seg_end[j] = idx;
    }
#ifdef PROFILE
    printf("thread %d: prepare for merge:    \t%ld ns\n", i, chrono::duration_cast<chrono::nanoseconds>(chrono::system_clock::now() - time_begin).count());
    auto local_time_begin = chrono::system_clock::now();
#endif
#ifdef DEBUG
#pragma omp master
{
    printf("swapped:\n");
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (i == swapped_local_begin[j] && ++j) printf("| ");
        printf("%d ", swapped_array[i]);
    }
    printf("|\n");
}
#endif

    // local merge
    using value_array_idx_pair = pair<int, int>;
    auto cmp = [](const value_array_idx_pair &a, const value_array_idx_pair &b) { return (a.first) > (b.first); };
    priority_queue<value_array_idx_pair, vector<value_array_idx_pair>, decltype(cmp)> min_heap(cmp);

    for (int j = 0; j < NUM_THREADS; j++) {
        if (local_seg_idx[j] < local_seg_end[j]) {
            min_heap.push({swapped_array[local_seg_idx[j]++], j});
        }
    }

    idx = swapped_local_begin[i];
    while (!min_heap.empty()) {
        auto min_pair = min_heap.top();
        min_heap.pop();
        if (local_seg_idx[min_pair.second] < local_seg_end[min_pair.second]) {
            min_heap.push({swapped_array[local_seg_idx[min_pair.second]++], min_pair.second});
        }
        result_array[idx++] = min_pair.first;
    }

#ifdef PROFILE
    printf("thread %d, merge:    \t%ld ns\n", i, chrono::duration_cast<chrono::nanoseconds>(chrono::system_clock::now() - local_time_begin).count());
#endif
}

    auto psrs_time_end = chrono::system_clock::now();
    auto psrs_sort_duration = chrono::duration_cast<chrono::nanoseconds>(psrs_time_end - psrs_time_begin);

#ifdef DEBUG
    printf("answer:\n");
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (i == swapped_local_begin[j] && ++j) printf("| ");
        printf("%d ", correct_answer[i]);
    }
    printf("|\n");
    printf("result:\n");
    j = 0;
    for (int i = 0; i < n; i++) {
        if (i == swapped_local_begin[j] && ++j) printf("| ");
        printf("%d ", result_array[i]);
    }
    printf("|\n");
#endif

    printf("=====================Summary=======================\n");
#ifndef ONLY_PSRS
    if (memcmp(correct_answer, result_array, sizeof(int) * n) == 0) {
        printf("\033[1;32mThe result is correct!\033[0m\n");
    }
    else {
        printf("\033[1;31mThe result is wrong!\033[0m\n");
    }
    printf("Quick Sort:\t %ld ns\n", qsort_duration.count());
#endif
    printf("PSRS Sort:\t %ld ns\n", psrs_sort_duration.count());
#ifndef ONLY_PSRS
    printf("speedup:\t %lf\n", qsort_duration.count() / (double)psrs_sort_duration.count());
#endif
    printf("===================================================\n");

}
