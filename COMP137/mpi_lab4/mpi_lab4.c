#include <stdio.h> 
#include <string.h>
#include <mpi.h> 
#include <time.h> 

const int MAX_STRING = 1000;
double MPI_Wtime(void);
clock_t clock(void);

// Wtime 0 -> not using Wtime, using regular c clock function
// Wtime 1 -> using MPI Wtime
#define Wtime 1

// message_len 1 -> default string 37 chars long
// message_len 2 -> 500 chars long 
// message_len 3 -> 1000 chars long
#define message_len 1

int main(void) {
	char message[MAX_STRING];
	int comm_sz;
	int my_rank;

	#if Wtime == 0
	clock_t start;
	start = clock();
	#endif

	// start up MPI 
	MPI_Init(NULL, NULL);

	// get num processes
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

	// get my rank among all processes
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	#if Wtime == 1
	double start;
	start = MPI_Wtime();
	#endif

	if(my_rank != 0) {
		sprintf(message, "This is message A from process %d of %d", my_rank, comm_sz);
		#if message_len == 1
		MPI_Send(message, strlen(message)+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
		#endif

		#if message_len == 2
		MPI_Send(message, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
		#endif

		#if message_len == 3
		MPI_Send(message, 1000, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
		#endif
	} else {
		printf("This is message B from process %d of %d\n", my_rank, comm_sz);
		for(int i = 1; i < comm_sz-1; i++) {
			MPI_Recv(message, MAX_STRING, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("%s\n", message);
		}
	}

//	printf("Message length: %d\n", (int)strlen(message));

	#if Wtime == 0
	printf("Using C clock function - average time taken for ping-pong communication: %fs\n", (float)((clock()-start)/(strlen(message))));
	#endif

	#if Wtime == 1
	printf("Using MPI Wtime - average time taken for ping-pong communication: %fs\n", (float)((MPI_Wtime()-start)/(strlen(message))));
	#endif

	// shut down MPI
	MPI_Finalize();

	return 0;
}
