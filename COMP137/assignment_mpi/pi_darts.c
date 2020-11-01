/*
 * Purpose: Estimate the value of PI using the dartboard method.
 *

 * Input:     None
 * Output:    Estimate of pi
 *
 * Program arguments:  <dart_count>
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

long long int global_sum; // global sum that local sums are being reduced to
int src = 0; // task that needs its data to be scattered
int sendcnt = 1; // number of things being sent 
int recvcnt = 1; // number of things being received

/* Serial function */
void Get_args(char* argv[],
      long long int* number_of_tosses_p);
void Usage(char* prog_name);


long long int Count_hits(long long int number_of_tosses);

/*---------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
	void *mem1 = malloc(sizeof(double));
	void *mem2 = malloc(sizeof(long long int));
   double *pi_estimate = (double *)mem1;
   long long int *number_in_circle = (int *)mem2;
   long long int *number_of_tosses = (int *)mem2;
	int comm_sz;
	int my_rank;

   if (argc != 2) Usage(argv[0]);
   Get_args(argv, number_of_tosses);

	// start up MPI
	MPI_Init(NULL, NULL); 
	
	// get num processes
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

	// get my rank among all processes
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	if(my_rank == 0) {
	MPI_Scatter(&number_of_tosses, sendcnt, MPI_LONG_LONG, &global_sum, recvcnt, MPI_LONG_LONG, src, MPI_COMM_WORLD); 
	}

   *number_in_circle = (long long int)Count_hits(number_of_tosses);

   pi_estimate = 4*(int)(&number_in_circle)/((int) (&number_of_tosses));
   printf("Estimated pi: %e\n", *&pi_estimate);

	MPI_Reduce(&*pi_estimate, &global_sum, &number_of_tosses, MPI_LONG_LONG, MPI_SUM, src, MPI_COMM_WORLD);

	if (my_rank == 0) {
		printf("Total sum = %lli\n", global_sum);
	}

	free(mem1);
	free(mem2);
	MPI_Finalize();

   return 0;
}

/*---------------------------------------------------------------------
 * Function:      Count_hits
 * Purpose:       Calculate number of hits in the unit circle
 * In arg:        number_of_tosses
 * Return val:    number_in_circle
 */

long long int Count_hits(long long int number_of_tosses) {

   long long int number_in_circle = 0;


      long long int toss;
      double x, y, distance_squared;
      srand (time (0));
      for(toss = 0; toss < number_of_tosses; toss++) {
         x = (double) rand () / RAND_MAX;
         y = (double) rand () / RAND_MAX;
         distance_squared = x*x + y*y;
         if (distance_squared <= 1) number_in_circle++;
      }


#  ifdef DEBUG
   printf("Total number in circle = %lld\n", number_in_circle);
#  endif

   return number_in_circle;
}  /* Count_hits */

/*---------------------------------------------------------------------
 * Function:  Usage
 * Purpose:   Print a message showing how to run program and quit
 * In arg:    prog_name:  the name of the program from the command line
 */

void Usage(char prog_name[] /* in */) {
   fprintf(stderr, "usage: %s ", prog_name);
   fprintf(stderr, "<total number of tosses>\n");
   exit(0);
}  /* Usage */

/*------------------------------------------------------------------
 * Function:    Get_args
 * Purpose:     Get the command line args
 * In args:     argv
 * Out args:    number_of_tosses_p
 */

void Get_args(
           char*           argv[]              /* in  */,
           long long int*  number_of_tosses_p  /* out */) {

   *number_of_tosses_p = strtoll(argv[1], NULL, 10);
}  /* Get_args */
