#include <stdio.h>
#include <cuda.h>

// size of the square matrix
#define N 4

// GPU kernel
__global__ 
void saxpy(int x, int *A, int *B, int *C){
	int i = threadIdx.x + blockDim.x * blockIdx.x;
        int j = threadIdx.y + blockDim.y * blockIdx.y;
        while (j < ((N*3)+1)){
                C[i+j] = x * A[i+j] + B[i+j];
                j++;
        }

}

//CPU function
void _saxpy(int x, int *A1, int *B1, int *C1){
      	for (int i = 0; i < N; ++i){
		C1[i] = x * A1[i] + B1[i];
	}
}

int main(int argc, char **argv){
	
	int a[N][N], b[N][N], c[N][N], c2[N][N];
 	int *dev_a, *dev_b, *dev_c;
 	int cont,i,j;

  	/* inicializando variables con datos foo*/
 	for (i = 0; i < N; i++) {
  		cont = 0;
  		for (j = 0; j < N; j++) {
   			a[i][j] = cont;
   			b[i][j] = cont;
   			cont++;
  		}
 	}

  	int size = N * N * sizeof(int);

  	cudaMalloc((void **) &dev_a, size);
 	cudaMalloc((void **) &dev_b, size);
 	cudaMalloc((void **) &dev_c, size);

  	cudaMemcpy(dev_a, a, size, cudaMemcpyHostToDevice);
 	cudaMemcpy(dev_b, b, size, cudaMemcpyHostToDevice);

  	dim3 dimGrid(1, 1);
 	dim3 dimBlock(N, N);

	clock_t start_d=clock();
    	printf("Doing GPU Vector app\n\n");
  	saxpy<<<dimGrid, dimBlock>>>(N * 3, dev_a, dev_b, dev_c);

	//Wait for kernel call to finish
    	cudaThreadSynchronize();

	clock_t end_d = clock();
    
    	printf("Doing CPU Vector app\n\n");
    	clock_t start_h = clock();
    	_saxpy(N * 3, (int *)a, (int *)b, (int *)c);
    	clock_t end_h = clock();

	//Time computing
    	double time_d = (double)(end_d-start_d)/CLOCKS_PER_SEC;
    	double time_h = (double)(end_h-start_h)/CLOCKS_PER_SEC;

  	cudaMemcpy(c2, dev_c, size, cudaMemcpyDeviceToHost);
	printf("n = %d \t GPU time = %fs \t CPU time = %fs\n\n", N, time_d, time_h);

  	cudaFree(dev_a);
 	cudaFree(dev_b);
 	cudaFree(dev_c);

	printf("-----------------------------------------------------------------------------------------------------------------------\n");

  	// imprimiendo
 	for (int y = 0; y < N; y++) {
  		for (int x = 0; x < N; x++) {
   			printf("[%d][%d]=%d ", y, x, c[y][x]);
  		}
  		printf("\n");
 	}

	printf("-----------------------------------------------------------------------------------------------------------------------\n");

	// imprimiendo
 	for (int y = 0; y < N; y++) {
  		for (int x = 0; x < N; x++) {
   			printf("[%d][%d]=%d ", y, x, c2[y][x]);
  		}
  		printf("\n");
 	}

  	return 0;
}

	


