/* COMP 137
 * filename: pthread_hello_timing_instrumentation.c
 * Hello printing threads. Code to illustrate use of
 * command line arguments, clock time collection and
 * external data storage.
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>       // clock()
#include <unistd.h>     // usleep()

/* global variables are shared by all threads */
const int MAX_THREADS = 256;
/* number of threads to be run */
short thread_count;
/* busy-wait flag to order threads */
long ready = -1;
/* array to hold timing data from threads */
float *wait_times;

/* get number of threads from the command line */
short processCommandLine(int argc, char* argv[]);
/* function that will be run by each thread */
void* hello(void* rank);
/* get current clock time (seconds) */
float getTime();
/* write a spreadsheet (CSV) file containing the timing information */
void recordWaitTimes();

/* main function - starting point for the main thread */
int main(int argc, char* argv[]) {
    long thread;
    pthread_t* thread_handles;

    thread_count = processCommandLine(argc, argv);

    /* create shared array for threads to store their wait time */
    wait_times = malloc(thread_count*sizeof(float));

    /* create an array of thread handles */
    thread_handles = malloc(thread_count*sizeof(pthread_t));

    /* start the threads, giving each a unique rank */
    for (thread = 0; thread < thread_count; thread++)
    {
        pthread_create(&thread_handles[thread], NULL,
          hello, (void*) thread);
    }

    /* print a message from the main thread */
    printf("Hello from the main thread\n");
    /* set busy-wait flag to allow thread 0 to go */
    ready = 0;

    /* wait for all threads to complete */
    for (thread = 0; thread < thread_count; thread++)
    {
        pthread_join(thread_handles[thread], NULL);
    }

    recordWaitTimes();

    /* delete the array of thread handles */
    free(wait_times);
    free(thread_handles);

    return 0;
}

/* function that will be run by each thread */
void* hello(void* rank) {
    /* Parameters to thread functions arrive as void pointers.
       They must be cast to their true type. */
    long my_rank = (long) rank;
    float time_1, time_2;

    /* busy-wait loop with timing instrumentation */
    time_1 = getTime();
    while (ready < my_rank) usleep(1);
    time_2 = getTime();
    wait_times[my_rank] = time_2 - time_1;

    /* print a message */
    printf("Hello from thread %ld of %d busy time = %f\n", my_rank, thread_count, wait_times[my_rank]);

    /* set busy-wait flag to allow next thread to go */
    ready = my_rank + 1;

    /*  Nothing to return. Return a NULL pointer. */
    return NULL;
}

/* get current clock time (seconds) */
float getTime()
{
    clock_t t = clock();
    return ((float)t)/CLOCKS_PER_SEC;
}

/* print command line usage message and error message and abort program. */
void usage(char* prog_name) {
   fprintf(stderr, "usage: %s <number of threads>\n", prog_name);
   fprintf(stderr, "0 < number of threads <= %d\n", MAX_THREADS);
   exit(0);
}

/* get number of threads from the command line */
short processCommandLine(int argc, char* argv[])
{
   if (argc != 2) usage(argv[0]);
   short thread_count = strtol(argv[1], NULL, 10);
   if (thread_count <= 0 || thread_count > MAX_THREADS) usage(argv[0]);
   return thread_count;
}

/* write a spreadsheet (CSV) file containing the timing information */
void recordWaitTimes()
{
    short i;
    FILE* fp = fopen("wait_times.csv", "w");
    if (fp == NULL)
    {
        fprintf(stderr, "failed to open wait_time.csv\n");
        return;
    }
    fprintf(fp, "core, wait time, wait time differential\n");
    for (i = 1; i<thread_count; i++)
    {
        fprintf(fp, "%d,%f,%f\n", i, wait_times[i], wait_times[i]-wait_times[i-1]);
    }
    fclose(fp);
}
