#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* In the figure 4.14, the output from line c and line p are 5 and 0. This is because
the parent is not being edited and the child is a copy of parent, which is being 
edited in the thread function *runner() */

int fib1, fib2; // this data is shared by the thread(s), generating fibonacci numbers
void *runner(void *param); // the thread


int main(int argc, char *argv[]) {
	pthread_t tid; //the thread identifier
	pthread_attr_t attr; //set of thread attributes
	
	if(argc != 2) {
		fprintf(stderr, "usage: a.out <integer value>\n");
		return -1;
	}
	if(atoi(argv[1]) < 0) {
		fprintf(stderr, "%d must be >= 0\n", atoi(argv[1]));
		return -1;
	}
	
	pthread_attr_init(&attr); // get the default attributes
	pthread_create(&tid, &attr, runner, argv[1]); // create the thread
	pthread_join(tid, NULL); // wait for the thread to exit

	return (0);
}


// the thread will begin control in this function
void *runner(void *param) {
	int upper = atoi(param), next;
	fib1 = 0;
	fib2 = 1;

	printf("Fibonacci series of %i: ", upper);

	for(int i = 0; i <= upper; i++) {
		if(i == upper) {
			printf("%d\n", fib1);
		}
		else {
			printf("%d, ", fib1);
		}
		next = fib1 + fib2;
		fib1 = fib2;
		fib2 = next;
	}

	pthread_exit(0);		
}

