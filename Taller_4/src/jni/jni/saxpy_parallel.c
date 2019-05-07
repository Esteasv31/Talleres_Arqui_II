#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <arm_neon.h>

int size[3] = {200000, 400000, 800000};

int main()
{
    int i;
    int z;
    int32_t k = rand() % 100;

    double start, run_time;

    for (z = 0; z < 3; z++)
    {
        int16_t *vector_A = (int16_t *)calloc(size[z], sizeof(int16_t));
        int16_t *vector_B = (int16_t *)calloc(size[z], sizeof(int16_t));
        int16_t *vector_C = (int16_t *)calloc(size[z], sizeof(int16_t));

        int16_t vector_D[4] = {k, k, k, k};

        for (i = 0; i <= size[z]; i++)
        {
            vector_A[i] = rand() % 100;
            vector_B[i] = rand() % 100;
        }

        // start timer

        start = omp_get_wtime();

        int16x4_t vector_1;
        int16x4_t vector_2;
        int16x4_t vector_3;
        int16x4_t vector_4 = vld1_s16(vector_D);

#pragma omp for

        for (i = 0; i <= size[z]; i += 4)
        {
            vector_1 = vld1_s16(vector_A);
            vector_A += 4;

            vector_2 = vld1_s16(vector_B);
            vector_B += 4;

            vector_3 = vmla_s16(vector_2, vector_1, vector_4);
            vst1_s16(vector_C, vector_3);
            vector_C += 4;
        }
        run_time = omp_get_wtime() - start;

        printf(" Run time: %f\n Size of array: %d\n\n", run_time, size[z]);
        free(*vector_A);
        free(*vector_B);
        free(*vector_C);
    }
}
