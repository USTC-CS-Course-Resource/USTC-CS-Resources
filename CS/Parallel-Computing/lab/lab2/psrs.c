#include "mpi.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    // init MPI
    int group_size, my_rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &group_size);

    // data size
    int n = 36;
    int step = n / group_size;
    int my_n = step;
    if (my_rank == group_size - 1) my_n = n - my_rank * step;

    // generate data
    srand(my_rank);
    int* my_array = malloc(my_n * sizeof(int));
    for (int i = 0; i < n; i++) {
        my_array[i] = rand() % (n - 0) + 0;
    }

    /************ begin ***********/
    printf("%d\n", my_n);

    // sort(my_array, my_array + my_n);
    for (int i = 0; i < my_n; i++) {
        printf("%d ", my_array[i]);
    }
    printf("\n");

    int my_sample_step = my_n / group_size;
    int* my_samples = malloc(group_size * sizeof(int));
    int* all_samples = malloc(16 * sizeof(int));
    for (int i = 0; i < group_size; i++) {
        my_samples[i] = my_array[i * my_sample_step];
        printf("%d from %d\n", my_samples[i], i * my_sample_step);
    }

    printf("size**2: %d\n", group_size*group_size);

    // sleep(10);
    // int* all_samples = (int*) malloc((group_size*group_size)*sizeof(int));
    // auto all_samples = new int[group_size * group_size];
    // int* all_samples = new int[group_size * group_size];
    // MPI_Gather(my_samples, group_size, MPI_INT,
    //     all_samples, group_size, MPI_INT, 0, MPI_COMM_WORLD);
    // if (my_rank == 0) {
    //     for (int i = 0; i < group_size * group_size; i++) {
    //         printf("%d ", all_samples[i]);
    //     }
    // }
    

    /************  end  ***********/
    MPI_Finalize();
}
