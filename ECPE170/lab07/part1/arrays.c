#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <stdint.h>

int main() 
{
	uint32_t two_array[3][5];   // A 2-dimensional array of 4-byte (32-bit) unsigned integers, i.e. uint32_t
	uint32_t three_array[3][5][7];   // A 3-dimensional array of 4-byte (32-bit) unsigned integers, i.e. uint32_t
	int i, j, k;
	long unsigned uint3, uint5, uint7;

	uint3 = sizeof(uint32_t)*3;
	uint5 = sizeof(uint32_t)*5;
	uint7 = sizeof(uint32_t)*7;

	//2-d array
	printf("Scanning and printing a 2-d array\n");
	printf("Utilization of memory(in bytes): \n");
	printf("Columns: %lu\n", uint3);
	printf("Row: %lu\n", uint5);
	printf("Total memory consumption: %lu\n", uint3+uint5);
	for(i=0; i<3; i++) {
		for (j=0; j<5;j++) {
			two_array[i][j] = rand() % 100;
		}

	}
	printf("Memory address of first element array[0][0] = %p\n", &two_array[0][0]);
	printf("Memory address of last element array[3][5] = %p\n", &two_array[3][5]);



	//3-d array
	printf("\nScanning and printing a 3-d array\n");
	printf("Utilization of memory(in bytes): \n");
	printf("Columns: %lu\n", uint3);
	printf("Row: %lu\n", uint5);
	printf("Depth: %lu\n", uint7);
	printf("Total memory consumption: %lu\n", uint3+uint5+uint7);
	for(i=0; i<3; i++) {
		for(j=0; j<5; j++) {
			for(k=0; k<7; k++) {
				three_array[i][j][k] = rand() % 100;
			}

		}

	}
	printf("Memory address of first element array[0][0][0] = %p\n", &three_array[0][0][0]);
	printf("Memory address of last element array[3][5][7] = %p\n", &three_array[3][5][7]);


return 0;
}
