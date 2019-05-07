#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int size[3] = {200000, 400000, 800000};

int main()
{
    int i;
    int z;
    int k = rand();
    double start, run_time;

    for (z = 0; z < 3; z++)
    {
        int16_t vector_A[size[z]];
        int16_t vector_B[size[z]];
        int16_t vector_C[size[z]];

        for (i = 0; i <= size[z]; i++)
        {
            vector_A[i] = rand() % 100;
            vector_B[i] = rand() % 100;
        }

        // start timer

        start = omp_get_wtime();

        for (i = 0; i <= size[z]; i++)
        {
            vector_C[i] = k * vector_A[i] + vector_B[i];
        }

        run_time = omp_get_wtime() - start;

        printf(" Run time: %f\n Size of array: %d\n\n", run_time, size[z]);
    }
}

