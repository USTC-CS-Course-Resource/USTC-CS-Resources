#include <stdio.h>
#include <omp.h>

static long num_steps = 10000000;
#define NUM_THREAD 2

double step;

void main() {
    double x, sum;
    double step = 1.0/(double)num_steps;

    omp_set_num_threads(NUM_THREAD);
#pragma omp parallel for reduction(+:sum) private(x)
    for (int i = 0; i < num_steps; i++) {
        x = (i + 0.5) *step;
        sum += 4.0 / (1.0 + x * x);
    }
    double pi = sum * step;
    printf("%lf\n", pi);
}