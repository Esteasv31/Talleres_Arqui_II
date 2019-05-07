#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <arm_neon.h>

int size[3] = {200000, 400000, 600000};

int main()
{
    int i;
    int z;
    int32_t k = rand() % 100;

    double start_time, run_time;

    for (z = 0; z < 3; z++)
    {
        int16_t *vecA = (int16_t *)calloc(size[z], sizeof(int16_t));
        int16_t *vecB = (int16_t *)calloc(size[z], sizeof(int16_t));
        int16_t *vecC = (int16_t *)calloc(size[z], sizeof(int16_t));

        int16_t vecD[4] = {k, k, k, k};

        for (i = 0; i <= size[z]; i++)
        {
            vecA[i] = rand() % 100;
            vecB[i] = rand() % 100;
        }

        // start timer

        start_time = omp_get_wtime();

        int16x4_t vec1;
        int16x4_t vec2;
        int16x4_t vec3;
        int16x4_t vec4 = vld1_s16(vecD);

#pragma omp for

        for (i = 0; i <= size[z]; i += 4)
        {
            vec1 = vld1_s16(vecA);
            vecA += 4;

            vec2 = vld1_s16(vecB);
            vecB += 4;

            vec3 = vmla_s16(vec2, vec1, vec4);
            vst1_s16(vecC, vec3);
            vecC += 4;
        }
        run_time = omp_get_wtime() - start_time;

        printf(" Run time: %f\n Size of array: %d\n\n", run_time, size[z]);
        free(*vecA);
        free(*vecB);
        free(*vecC);
    }
}
