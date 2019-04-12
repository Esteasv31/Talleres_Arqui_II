
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
	 * Temporary matrix ready to store input values
	 */

	short fxc[2][8];

	/**
	 * Get input from user into a temporary matrix
	 */

	printf(" ****************** Matrix input ******************\n");
	int i, j;
	for (j = 0; j < 2; j++){
		for (i = 0; i < 8; i++){
			int datatemp;
			printf("Enter value for position [%d] [%d]: ", j, i);
			scanf("%d", &datatemp);
			fxc[j][i] = datatemp;
			printf("\n");
		}
	}

	/**
	 * Get inputs from the temporary matrix into the vectors
	 */

	__m128i vector1 = _mm_set_epi16(fxc[0][7], fxc[0][6], fxc[0][5], fxc[0][4], fxc[0][3], fxc[0][2], fxc[0][1], fxc[0][0]);
	__m128i vector2 = _mm_set_epi16(fxc[1][7], fxc[1][6], fxc[1][5], fxc[1][4], fxc[1][3], fxc[1][2], fxc[1][1], fxc[1][0]);
	
	/**
	 * Get the highest value for each column on each vector
	 */

	__m128i result = _mm_max_epi16(vector1, vector2);

	/**
	 * Instantiate variables to extract values from vectors
	 */

	short* vect1 = (short*) &vector1;
	short* vect2 = (short*) &vector2;
	short* data = (short*) &result;

	/**
	 * Print input matrix
	 */

	printf(" ***************************** Input Matrix ***************************** \n");
	for(i=0; i<8; i++){
		printf("%d \t", *(vect1+i));
	}
	printf("\n");
	
	for(i=0; i<8; i++){
		printf("%d \t", *(vect2+i));
	}
	printf("\n\n");
	
	/**
	 * Print resulting vector
	 */

	printf(" ************************* Resulting Vector ************************* \n");
	for(i=0; i<8; i++){
		printf("%d \t", *(data+i));
	}
	printf("\n");

	return 1;
}
