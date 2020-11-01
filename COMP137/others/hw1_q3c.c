#include <stdio.h>
#include <math.h>

float D(int p);

int main() {
	// t_serial = pow((20*n),2) + C; 
	// t_parallel = (pow((20*n),2) * p) + C + D;
	int C = 100;
	// p = n = malloc(8*sizeof(int)); 

	for (int i = 0; i <= 10; i++) {
		float s = (pow((20*(pow(2,i))),2) + C)/((pow((20*(pow(2,i))),2) * (pow(2,i))) + C + D(pow(2,i)));
		printf("S 2^%i = %4f \n", i, s); 
		printf("E 2^%i = %4f \n", i, (s/(pow(2,i))));
	}

	return 0;
}

float D(int p) {
	return 10 * log2(p);
}

