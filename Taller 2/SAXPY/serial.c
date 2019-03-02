/*
 * Created by Esteban Sanabria on 2/24/19.
 *
 * This program will compute SAXPY algorithm for Matrixes
 *
 *  y[i] = a*x[i] + y[i];
 *
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define Size 100000 // Size for arrays to be used
#define a 10 // Constant for SAXPY algorithm

int main (){

    double start_time, run_time;

    int i, j; // Loop indexes

    for (int run = 1; run < 4; run ++){

        int arraySize = Size * run;

        float x[arraySize]; // array "x"
        float y[arraySize]; // array "y"

        // Loop to fill the arrays "x" and "y" with random values
        for (i = 0; i < arraySize; i++) {
            x[i] = rand() % 999; // Random number in range from 0 to 999
            y[i] = rand() % 999; // Random number in range from 0 to 999
        }

        //Loop to executes SAXPY algorithm with "x" and "y" using "a" as const
        start_time = omp_get_wtime();

        for (j = 0; j < arraySize; j++) {
            y[j] = a*x[j] + y[j]; // SAXPY function
        }

        run_time = omp_get_wtime() - start_time;
        printf("Run time = %f for array of size %d\n", run_time, arraySize);

    }

    return 0;
}