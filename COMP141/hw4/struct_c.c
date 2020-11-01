#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/* custom struct int_to_int */
struct int_to_int {
	int val[50];
};


/* function prototypes */
void map_array(struct int_to_int f, int a[], int size);	// applies a function to the contents of an array
int times2(int x);										// doubles the value


int main() {
	srand(time(0));
	int size = (rand() % 10) + 1;
	int* a = malloc(size * sizeof(int));
	int* val = malloc(size * sizeof(int)); 
	struct int_to_int yikes;

	printf("orginal array a = [");
	for (int i = 0; i < size-1; i++) {
		a[i] = (rand() % 50) + 1;
		printf(" %i ", a[i]);
	}
	printf("]\n");

	printf("resulting array val = ["); 
	map_array(yikes, a, size);
	printf("]\n");

	free(a);
	free(val);

	return 0; 
}


int times2(int x) {
	return x*2;
}


void map_array(struct int_to_int f, int a[], int size) {
	for (int i = 0; i < size-1; i++) {
		f.val[i] = times2(a[i]);
		printf(" %i ", f.val[i]);
	} 
} 

