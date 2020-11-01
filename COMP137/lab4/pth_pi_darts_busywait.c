/* COMP 137 Spring 2019
 * filename: pth_pi_darts_busywait.c
 *
 * Purpose: Estimate the value of PI using the dartboard method.
 *          Thread synchronization via busy-wait.
 *
 * Program arguments: <thread_count> <dart_count>
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>       // clock()
#include <unistd.h>     // usleep()

#define ALLOW_PRINT_FROM_THREADS

const int MAX_THREADS = 1024;

/* global values that are extracted from the command line */
long thread_count = 0;
long dart_count = 0;
long darts_per_thread = 0;

/* forward reference functions */
void extractCommandLineArgs(int argc, char* argv[]);
void *threadWork(void* args);  /* Thread function */
float getTime();

/* structure passed as argument to new threads */
typedef struct
{
    long rank;
    long rand_seed;
    long num_darts;
} THREAD_ARG;

/* global variables for communication */
long total_hits;
short ready_flag = -1;

/*--------------------------------------------------------------------*/
int main(int argc, char* argv[])
{
    long t_rank;
    pthread_t* thread_handles;
    THREAD_ARG* thread_arguments;
    double PI;
    float time1, time2;

    extractCommandLineArgs(argc, argv);
    printf("Using %ld threads to throw %ld darts\n", thread_count, dart_count);

    /* allocate thread handles */
    thread_handles =
        (pthread_t*)malloc(thread_count*sizeof(pthread_t));
    /* allocate thread argument structures */
    thread_arguments =
        (THREAD_ARG*)malloc(thread_count*sizeof(THREAD_ARG));

    srand(time(0)); /* seed the random number generator */
    time1 = getTime(); /* get a start time from the clock */

    /* create the threads, give each a unique rank, a random number
     *   and the number of darts they need to throw. */
    for (t_rank = 0; t_rank < thread_count; t_rank++)
    {
        thread_arguments[t_rank].rank = t_rank;
        thread_arguments[t_rank].rand_seed = rand();
        thread_arguments[t_rank].num_darts = darts_per_thread;
        pthread_create(&thread_handles[t_rank],
                       NULL,
                       threadWork,
                       (void*) &(thread_arguments[t_rank])
                       );
    }
    printf("Main thread: All threads have been created.\n");

    /* signal thread 0 that it can access the shared sum. */
    total_hits = 0;
    ready_flag = 0;

    /* wait for all threads to finish */
    for (t_rank = 0; t_rank < thread_count; t_rank++)
        pthread_join(thread_handles[t_rank], NULL);

    time2 = getTime(); /* get an end time from the clock */
    printf("Main thread: All threads have completed.\n");

    /* compute and print results */
    PI = 4.0*total_hits/dart_count;
    printf("Main thread: total hits = %ld from %ld darts.\n",
           total_hits, dart_count);
    printf("Main thread: PI = %lf.\n", PI);
    printf("Main thread = total time: %f seconds.\n", time2-time1);

    /* clean up dynamically allocated memory */
    free(thread_handles);
    free(thread_arguments);
    return 0;
}

/*-------------------------------------------------------------------*/
/* get a random real number within range [min,max] */
double frand_range(double min, double max)
{
    return (max-min)*((float)rand()/(float)RAND_MAX) + min;
}

/*-------------------------------------------------------------------*/
void *threadWork(void* argstruct)
{
    /* unpack the thread arguments */
    long my_rank = ((THREAD_ARG*)argstruct)->rank;
    long my_rand_seed = ((THREAD_ARG*)argstruct)->rand_seed;
    long my_dart_cnt = ((THREAD_ARG*)argstruct)->num_darts;

    double my_radius = 1.0; /* radius of the circle */
    long my_hits = 0;
    long my_dart;

#ifdef ALLOW_PRINT_FROM_THREADS
    printf("Thread %ld: started with random seed %ld and dart count %ld.\n",
           my_rank, my_rand_seed, my_dart_cnt);
#endif

    srand(my_rand_seed); /* seed my random number generator */

    /* throw the darts */
    for (my_dart=0; my_dart<my_dart_cnt; my_dart++)
    {
        double x = frand_range(-my_radius,my_radius);
        double y = frand_range(-my_radius,my_radius);
        double d = sqrt(x*x+y*y);
        if (d <= my_radius) my_hits++;
    }

#ifdef ALLOW_PRINT_FROM_THREADS
    printf("Thread %ld: %ld darts thrown, %ld hits.\n",
           my_rank, my_dart_cnt, my_hits);
#endif

    /* wait for access to shared sum variable */
    while (ready_flag < my_rank) usleep(1);
    /* store hits in sum workspace */
    total_hits += my_hits;

    /* pass shared sum access to next thread */
    ready_flag = my_rank + 1;

    return NULL;
}

/*-------------------------------------------------------------------*/
// current clock time (seconds)
float getTime()
{
    clock_t t;
    t = clock();
    return ((float)t)/CLOCKS_PER_SEC;
}

/*-------------------------------------------------------------------*/
void usage(char* prog_name)
{
    fprintf(stderr, "usage: %s <number of threads> <number of darts>\n",
            prog_name);
    fprintf(stderr, "0 < number of threads <= %d\n", MAX_THREADS);
    exit(0);
}

/*--------------------------------------------------------------------*/
void extractCommandLineArgs(int argc, char* argv[])
{
    if (argc != 3) usage(argv[0]);
    thread_count = strtol(argv[1], NULL, 10);
    if (thread_count <= 0 || thread_count > MAX_THREADS) usage(argv[0]);
    dart_count = strtol(argv[2], NULL, 10);
    if (dart_count <= 0) usage(argv[0]);
    darts_per_thread = dart_count / thread_count;
    dart_count = darts_per_thread * thread_count;
}
