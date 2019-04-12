
/**  Taller 3 - Arquitectura de Computadores II
 *	 Author: Esteban Sanabria Villalobos
 *	 Instituto Tecnológico de Costa Rica
 *	 I Semestre, 2019
 */


#include <emmintrin.h>
#include <smmintrin.h>
#include <stdio.h>

int main (){

	/**
	 * Instance matrixes to be used in the algorithm
	 */

	__m128i matrix1[4];
	__m128i matrix2[4];
	int result[4][4];
	
	/**
	 * Fill matrix1, each vector represents a row
	 */

	matrix1[0] = _mm_set_epi32(4,3,2,1);
	matrix1[1] = _mm_set_epi32(4,3,2,1);
	matrix1[2] = _mm_set_epi32(4,3,2,1);
	matrix1[3] = _mm_set_epi32(4,3,2,1);

	/**
	 * Fill matrix2, each vector represents a column
	 */

	matrix2[0] = _mm_set_epi32(1,1,1,1);
	matrix2[1] = _mm_set_epi32(2,2,2,2);
	matrix2[2] = _mm_set_epi32(3,3,3,3);
	matrix2[3] = _mm_set_epi32(4,4,4,4);

	/**
	 * Matrix multiplication
	 */

	int i,j;
	for(i = 0; i < 4; i++){
		for (j = 0; j < 4; ++j){
			__m128i _result = _mm_mullo_epi32(matrix1[i], matrix2[j]); // Multiply each value of each vector (row times column)
			int* res = (int*) &_result; 								  // Pointer to extract the results
			result[i][j] = *(res) + *(res+1) + *(res+2) + *(res+3);   // Add mult results to get dot product and add value to the resulting matrix
		}
	}

	/**
	 * Function to print the matrix1
	 */

	printf("********************************* Matrix 1 *********************************\n");
	for(i = 0; i < 4; i++){
		int* vect1 = (int*) &matrix1[i];
		printf("%d\t%d\t%d\t%d\t", *(vect1),*(vect1+1),*(vect1+2),*(vect1+3));
		printf("\n");
	}

	/**
	 * Function to print the matrix2
	 */

	printf("********************************* Matrix 2 *********************************\n");
	for(i = 0; i < 4; i++){
		for (j = 0; j < 4; ++j){
			int* vect1 = (int*) &matrix2[j];
			printf("%d\t", *(vect1+i));
		}
		printf("\n");
	}
	
	/**
	 * Print the resulting matrix
	 */

	printf("**************************** Resulting Matrix ****************************\n");
	for(i = 0; i < 4; i++){
		for (j = 0; j < 4; ++j){
			printf("%d\t", result[i][j]);
		}
		printf("\n");
	}

	return 1;
}
