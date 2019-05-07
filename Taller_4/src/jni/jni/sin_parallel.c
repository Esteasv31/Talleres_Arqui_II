#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

static long steps = 100000000;
double step;

int factorial(int n)
{

    int fac = 1;
    int i;
    if (n == 0 || n == 1)
    {
        return 1;
    }
    else
    {
        for (i = 1; i <= n; i++)
        {
            fac = fac * i;
        }
        return fac;
    }

    return 0;
}

int main()
{
    double start, run_time;
    double k;
    double f1, f2, f;
    double n = 17;
    float angle = 0.5;
    float sin = 0.0;

    start = omp_get_wtime();
#pragma opm parallel for private(k, n) reduction(+ \
                                                 : seno)
    {
        for (k = 0; k < n; k++)
        {
            f1 = pow(-1, k);
            f2 = pow(angle, 2 * k + 1);
            f = factorial(2 * k + 1);
            sin += f1 * f2 / f;
        }
    }
    run_time = omp_get_wtime() - start;

    printf(" Run time: %f\n", run_time);
    fflush(stdout);
    printf(" Sin , iterations, angle = [%f, %f, %f ]\n", sin, n, angle);
    fflush(stdout);

    return 0;
}

