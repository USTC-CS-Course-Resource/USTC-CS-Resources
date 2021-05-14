// pc_lab1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <chrono>
#include <cstdlib>
#include <omp.h>

#define NUM_THREADS 4

using namespace std;

int main()
{
    int n = 100000;
    srand(0);
    auto array = new int[n];
    auto correct_answer = new int[n];
    for (int i = 0; i < n; i++) {
        int tmp = rand() % (n - 0) + 0;
        array[i] = tmp;
        correct_answer[i] = tmp;
    }

    // begin timing for quick sort
    auto time_begin = chrono::system_clock::now();
    sort(correct_answer, correct_answer + n);
    auto time_end = chrono::system_clock::now();
    auto quick_sort_duration = chrono::duration_cast<chrono::nanoseconds>(time_end - time_begin);
    // end timing for quicksort

    // begin timing for psrs sort
    time_begin = chrono::system_clock::now();
    // size of divided array
    int step = ceil((double)n / NUM_THREADS);

	omp_set_num_threads(NUM_THREADS);

    int samples[NUM_THREADS * NUM_THREADS] = {0};
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
    printf("local sort:\n");
    for (int i = 0; i < n; i++) {
        if (i % step == 0) printf("| ");
        printf("%d ", array[i]);
    }
    printf("|\n");
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
#pragma omp parallel
{
    int i = omp_get_thread_num();
    for (int j = 0; j < NUM_THREADS; j++) {
        swapped_local_n[i] += seg_idx[j][i+1] - seg_idx[j][i];
    }
}
    int swapped_local_begin[NUM_THREADS + 1] = {0};
    for (int i = 1; i <= NUM_THREADS; i++) {
        swapped_local_begin[i] = swapped_local_begin[i-1] + swapped_local_n[i-1];
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
    
    // do swap and local sort
    int swapped_array[n];
#pragma omp parallel
{
    int i = omp_get_thread_num();
    int idx = swapped_local_begin[i];
    for (int j = 0; j < NUM_THREADS; j++) {
        for (int k = seg_idx[j][i]; k < seg_idx[j][i+1]; k++) {
            swapped_array[idx++] = array[k];
        }
    }
    // local sort again
    sort(swapped_array + swapped_local_begin[i], swapped_array + swapped_local_begin[i] + swapped_local_n[i]);
}
    time_end = chrono::system_clock::now();
    auto psrs_sort_duration = chrono::duration_cast<chrono::nanoseconds>(time_end - time_begin);

#ifdef DEBUG
    printf("result:\n");
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (i == swapped_local_begin[j] && ++j) printf("| ");
        printf("%d ", swapped_array[i]);
    }
    printf("|\n");
#endif

    printf("=====================Summary=======================\n");
    if (memcmp(correct_answer, swapped_array, sizeof(int) * n) == 0) {
        printf("\033[1;32mThe result is correct!\033[0m\n");
    }
    else {
        printf("\033[1;31mThe result is wrong!\033[0m\n");
    }
    printf("Quick Sort:\t %ld ns\n", quick_sort_duration.count());
    printf("PSRS Sort:\t %ld ns\n", psrs_sort_duration.count());
    printf("===================================================\n");

}
