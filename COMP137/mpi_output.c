/* File:     mpi_output.c
 *
 * Purpose:  A program in which multiple MPI processes try to print 
 *           a message.
 *
 * Compile:  mpicc -g -Wall -o mpi_output mpi_output.c
 * Usage:    mpiexec -n<number of processes> ./mpi_output
 *
 * Input:    None
 * Output:   A message from each process
 *
 * IPP:      Section 3.3.1  (pp. 97 and ff.)
 */
#include <stdio.h>
#include <string.h> 
#include <mpi.h> 

const int MAX_STRING = 100;

int main(void) {
   int my_rank, comm_sz;		// my process rank + number of processes
	char toothpick[MAX_STRING]; // string storing message

   MPI_Init(NULL, NULL); 					// starting an MPI
   MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); // get num of processes 
   MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); // get my rank among all processes

	if (my_rank != 0) {
	   sprintf(toothpick, "Proc %d of %d > Does anyone have a toothpick?\n", my_rank, comm_sz); // creating a message
      MPI_Send(toothpick, strlen(toothpick)+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD); //send message to process 0
	} else { 
	   printf("Proc %d of %d > Does anyone have a toothpick?\n", my_rank, comm_sz); // printing my message 
		for (int i = 1; i < comm_sz; i++) {
			/* Receive message from process i */
		     MPI_Recv(toothpick, MAX_STRING, MPI_CHAR, i,
		        0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		     /* Print message from process i */
		     printf("%s\n", toothpick);
		}
	}

   MPI_Finalize(); //shuts down MPI
   return 0;
}  /* main */
