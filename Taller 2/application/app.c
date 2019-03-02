/*
 * Created by Esteban Sanabria on 2/24/19.
 *
 * This program will compute the integral of sen(x) + 1 using the mid point rule and  OpenMP
 *  in order to optimize the process
 *
 *   integral = sen(x) +1
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main (){

    int numPartitions = 100000000; //Number of segments in which the integral will be divided
    double interval = 0;
    double integral;
    double a = 0;
    double b = 0;

    interval = 5 * M_PI / (double) numPartitions;

    double start = omp_get_wtime();

    for (int i = 0; i < numPartitions; i++) {

        b = i * interval;

        a = b + interval;

        integral += sin((b + a) / 2) + 1.0 ;
    }

    integral *= interval;

    double end = omp_get_wtime();

    printf("Estimate of integral is: %10.8lf and the Time = %lf  (Serial Case)\n", integral, end - start);

    start = omp_get_wtime();

    #pragma omp parallel num_threads(4 * omp_get_num_procs())
    {
        #pragma omp for firstprivate(b,a) reduction(+:integral)

        for (int i = 0; i < numPartitions; i++) {

            b = i * interval;

            a = b + interval;

            integral += sin((b + a) / 2) + 1.0 ;
        }

    }

    integral *= interval;

    end = omp_get_wtime();

    printf("Estimate of integral is: %10.8lf and the Time = %lf  (Parallel Case)\n", integral, end - start);

    return 0;


}