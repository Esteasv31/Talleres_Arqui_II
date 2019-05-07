#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int size[3] = {200000, 400000, 600000};

int main()
{
    int i;
    int z;
    int k = rand();
    double start_time, run_time;

    for (z = 0; z < 3; z++)
    {
        int16_t vecA[size[z]];
        int16_t vecB[size[z]];
        int16_t vecC[size[z]];

        for (i = 0; i <= size[z]; i++)
        {
            vecA[i] = rand() % 100;
            vecB[i] = rand() % 100;
        }

        // start timer

        start_time = omp_get_wtime();

        for (i = 0; i <= size[z]; i++)
        {
            vecC[i] = k * vecA[i] + vecB[i];
        }

        run_time = omp_get_wtime() - start_time;

        printf(" Run time: %f\n Size of array: %d\n\n", run_time, size[z]);
    }
}

