//
// Created by vidarr on 2/24/19.
//

void saxpy(int n, float a, float * restrict x, float * restrict y)
{
    for (int i = 0; i < n; ++i)
        y[i] = a*x[i] + y[i];
}


// Perform SAXPY on 1M elements
saxpy(1<<20, 2.0, x, y);