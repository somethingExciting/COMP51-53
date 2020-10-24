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
#include <omp.h> 

/* Serial function */
void Get_args(char* argv[],
      long long int* number_of_tosses_p);
void Usage(char* prog_name);
double omp_get_wtime(void);


long long int Count_hits(long long int number_of_tosses);

/*---------------------------------------------------------------------*/
int main(int argc, char* argv[]) {
   double pi_estimate = 0.0;
   int thread_count = 4;
   long long int number_in_circle = 0;
   long long int number_of_tosses = 0;
	double start = omp_get_wtime();

   if (argc != 2) Usage(argv[0]);
   Get_args(argv, &number_of_tosses);

# pragma omp parallel num_threads(thread_count)
   number_in_circle = Count_hits(number_of_tosses);

# pragma omp barrier

   pi_estimate = 4*number_in_circle/((double) number_of_tosses);
   printf("Estimated pi: %e\n", pi_estimate);

	printf("Time taken for pi_darts.c: %fs\n", ((double)(omp_get_wtime()-start)));

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
      srand(time(NULL));
# pragma omp parallel for private(toss,x,y,distance_squared) reduction(+:number_in_circle)
      for(toss = 0; toss < number_of_tosses; toss++) {
         x = (double) rand () / RAND_MAX;
         y = (double) rand () / RAND_MAX;
# pragma omp critical 
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
