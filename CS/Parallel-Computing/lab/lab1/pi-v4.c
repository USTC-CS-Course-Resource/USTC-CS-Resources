#include <stdio.h>
#include <omp.h>

static long num_steps = 1000000000;
#define NUM_THREAD 16

double step;

int main() {
    double pi;
    double step = 1.0/(double)num_steps;

    omp_set_num_threads(NUM_THREAD);
#pragma omp parallel
{
    double x;
    int id = omp_get_thread_num();
    double sum;
    for (int i = 0; i < num_steps; i += NUM_THREAD) {
        x = (i + 0.5) *step;
        sum += 4.0 / (1.0 + x * x);
    }
#pragma omp critical
    pi += step * sum;
}
    printf("%lf\n", pi);
}