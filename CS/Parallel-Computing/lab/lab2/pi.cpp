#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char* argv[]) {
    int group_size, my_rank;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &group_size);

    long n = 10000000000;
    MPI_Bcast(&n, 1, MPI_LONG, 0, MPI_COMM_WORLD);
    double h = 1.0 / (double)n;
    double sum = 0.0;
    for (long i = my_rank + 1; i <= n; i += group_size) {
        double x = h * (i - 0.5);
        sum += 4.0 / (1.0 + x * x);
    }
    double mypi = h * sum;
    double pi;
    MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if (my_rank == 0) {
        printf("pi is approximately: %.16lf\n", pi);
    }

    MPI_Finalize();
}