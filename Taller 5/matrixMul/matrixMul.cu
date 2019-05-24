#include <stdio.h>
#include <cuda.h>

// size of the square matrix
#define N 4

//Cuda error checking - non mandatory
void cudaCheckError() {
	cudaError_t e=cudaGetLastError();
	if(e!=cudaSuccess) {
		printf("Cuda failure %s:%d:'%s'\n",__FILE__,__LINE__,cudaGetErrorString(e));
  		exit(0);
 	}
}

// GPU kernel
__global__ void matrixMul(int *A, int *B, int *C){
	int k;
	int sum = 0;
	int col = threadIdx.x + blockDim.x * blockIdx.x;	
	int row = threadIdx.y + blockDim.y * blockIdx.y;
	if (col < N && row < N) {
  		for (k = 0; k < N; k++) {
   			sum += A[row * N + k] * B[k * N + col];
  		}
  		C[row * N + col] = sum;
 	}
}

//CPU function
void matrix_Mul(int A1[][N], int B1[][N], int C1[][N]){
        int n = 0;
	int m = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
   			int sum = 0;
			for (int k = 0; k < N; k++) {
    				m = A1[i][k];
    				n = B1[k][j];
    				sum += m * n;
   			}
   			C1[i][j] = sum;
  		}
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
    	printf("Doing GPU Vector mulMatrix\n\n");
  	matrixMul<<<dimGrid, dimBlock>>>(dev_a, dev_b, dev_c);
	cudaCheckError();

	//Wait for kernel call to finish
    	cudaThreadSynchronize();

	clock_t end_d = clock();
    
    	printf("Doing CPU Vector mulMatrix\n\n");
    	clock_t start_h = clock();
    	matrix_Mul(a, b, c);
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

	


