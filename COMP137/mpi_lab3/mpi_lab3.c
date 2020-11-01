#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include <time.h>

const long long MAX_LEN = 65536;
float global_sum = 0;
int sendcnt = 1; //sending 1 data 
int recvcnt = 1; //sending 1 data
int src = 0;	//the task that needs its data to be scattered
double MPI_Wtime( void );

// VERSION 1 -> using MPI_Scatter and MPI_Reduce
// VERSION 2 -> using MPI_Send and MPI_Recv 
#define VERSION 2

int main(void) {
	srand(time(NULL));
	int calculate[MAX_LEN];
	float local_sum = 0;
	int comm_sz;
	int my_rank;
	double start;

#if VERSION == 1 //MPI_Reduce & MPI_Scatter
	// start up MPI
	MPI_Init(NULL, NULL);

	// get num processes
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

	// get my rank among all processes
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	start = MPI_Wtime();
	if (my_rank == 0) {
		printf("Processor %d has data: ", my_rank);
		for(int i = 0; i < MAX_LEN-1; i++) {
			calculate[i] = (double)rand()/100.0*2.0-1.0;
			local_sum += calculate[i];
		}
		printf("\n");
	}
	// scattering the local sums to different processes
	MPI_Scatter(calculate, sendcnt , MPI_INT, &global_sum, recvcnt, MPI_INT, src, MPI_COMM_WORLD); 

	// printing the random numbers on each process
	printf("Local sum for process %d - %f, avg = %f\n", my_rank, local_sum, (local_sum/MAX_LEN)); 

	// reduce all local sums into a global sum 
	MPI_Reduce(calculate, &global_sum, sendcnt, MPI_FLOAT, MPI_SUM, src, MPI_COMM_WORLD);

	if (my_rank == 0) {
		printf("Total sum = %f, avg = %f\n", global_sum, (global_sum / MAX_LEN));
	}
	printf("Time taken for Version 1 run: %f\n", (float)(MPI_Wtime()-start));
#endif

#if VERSION == 2 //MPI_Send & MPI_Recv
	// start up MPI
	MPI_Init(NULL, NULL);

	// get num processes
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

	// get my rank among all processes
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	start = MPI_Wtime();
	if (my_rank != 0) {	
		for (int i = 0; i < MAX_LEN-1; i++) {
			local_sum += calculate[i];
		}
		MPI_Send(calculate, sendcnt, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	} else { 
		for(int i = 0; i < MAX_LEN-1; i++) {
			calculate[i] = (double)rand()/100.0*2.0-1.0;
			local_sum += calculate[i];
		}
		for (int i = 1; i < comm_sz-1; i++) {
			MPI_Recv(calculate, MAX_LEN, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("%d\n", calculate[i]);
		}
	}
	printf("Time taken for Version 2 run: %f\n", (float)(MPI_Wtime()-start));
#endif

	MPI_Finalize();

	return 0;
} 
