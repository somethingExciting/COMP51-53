/*
Purpose:	Simulate A* with the parallelization of Dijkstra's algorithm (since they both aim to find the shortest optimal path from point A to point B).
Compile:	gcc -g -Wall -fopenmp -o a-star a-star.c -lm
Run:		./a-star <number of vertices> <number of threads>
*/
#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>
#include <time.h>
#include <omp.h>

// static variables
#define INFIN 9999

// global variables
int startnode = 0, thread_count = 0, vertices = 0, rows = 0, cols = 0;
int** cost  = NULL; // cost matrix
int* distance = NULL;
int* prev = NULL;
int* visited = NULL;

// function prototypes
void a(int** G, int rows, int cols);
double omp_get_wtime(void);

/*
function: main driver 
input: argc - argument counter
	   argv - argument vector
output: N/A
*/
int main(int argc, char *argv[]) {
	srand(time(NULL));
	int** map = NULL;
	double start, finish;
	int i, j;
/*
	int matrix[10][10] = {
    {1, 10, 0, 4, 0, 0, 8, 0, 0, 3},
    {2, 0, 9, 0, 0, 2, 0, 0, 0, 1},
    {1, 1, 0, 7, 2, 0, 0, 8, 0, 1},
    {2, 4, 0, 0, 0, 1, 1, 1, 3, 4},
    {2, 1, 3, 1, 0, 11, 0, 1, 0, 10},
    {1, 9, 0, 12, 0, 6, 0, 1, 3, 3},
    {9, 0, 2, 1, 1, 6, 1, 1, 0, 1},
    {0, 3, 0, 0, 9, 10, 8, 0, 0, 1},
    {1, 0, 0, 2, 0, 0, 9, 9, 0, 1},
    {1, 0, 11, 0, 1, 1, 1, 4, 7, 1}
}; */

	if (argc > 3 || argc < 0) {
		printf("Invalid amount of arguments. Input is <executable> <number of vertices> <number of threads>\n");
		exit(0);
	}
	vertices = atoi(argv[1]);
	thread_count = atoi(argv[2]);

/*
	if(atoi(argv[1])%atoi(argv[2]) != 0) {
		printf("Enter a number of vertices that is evenly divisible by number of threads.\n");
		exit(0);
	}
*/

	rows = cols = floor(sqrt(vertices));
	
	map = (int **)malloc(rows*sizeof(int*));
	for (i = 0; i < rows; i++) {
		map[i] = (int *)malloc(cols*sizeof(int));
		for (j = 0; j < cols; j++) {
			map[i][j] = rand() % 1000;
		}
	}

	/* STARTING PARALLELIZATION */

	start = omp_get_wtime();
#pragma omp parallel num_threads(thread_count)

	a(map, rows, cols);

	finish = omp_get_wtime();

	printf("A* took %fs to execute with %d vertices and %d thread(s)\n", ((float)(finish-start)), vertices, thread_count);

	/* END OF PARALLELIZATION */


	for(i = 0; i < rows; i++) {
		free(map[i]);
		free(cost[i]);
	} free(map);
	free(cost);
	free(distance);
	free(prev);
	free(visited);

	return 0;
}

/*
function: traverses a graph and finds the shortest path 
input: int** G - the graph/matrix that is being traversed
	   int rows - the number of rows in the matrix
	   int cols - the number of columns in the matrix
output: N/A  
*/
void a(int** G, int rows, int cols) {
	distance = (int *)malloc(rows*sizeof(int));	// distances btwn nodes
	prev = (int *)malloc(rows*sizeof(int));		// previous nodes
	visited = (int *)malloc(rows*sizeof(int));		// visited path
	int count = 0;										// number of nodes seen so far
	int min_dis, nextnode, i ,j;						// minimum distance, next node

	// creating memory for the cost matrix
	cost = (int **)malloc(rows*sizeof(int*));
	for(i = 0; i < rows; i++) {
		cost[i] = (int *)malloc(cols*sizeof(int));
	} 

//	printf("create cost matrix");

	// creating the cost matrix 
	#pragma omp parallel for
	for(i = 0; i < rows; i++) {
		for(j = 0; j < cols; j++) {
			if (G[i][j] == 0) {
				cost[i][j] = INFIN;
			}
			else {
				cost[i][j] = G[i][j];
			}
		}
	}

//	printf("initializing distanc prev visited");

	// initializing distance, prev, visited
	#pragma omp parallel for
	for (i = 0; i < rows; i++) {
		distance[i] = cost[startnode][i];
		prev[i] = startnode;
		visited[i] = 0;
	} 

	distance[startnode] = 0;
	visited[startnode] = 1;
	count = 1;

//	printf("traversing graph for a shorter path");

	// traverse the graph/matrix for a shorter path
	while(count < rows-1) {
		min_dis = INFIN;
		for (i = 0; i < rows; i++) {
			if(distance[i] < min_dis && !visited[i]) {
				#pragma omp critical
				min_dis = distance[i];
				visited[i] = i;
			}
			visited[nextnode] = 1; 
			if(!visited[i]) {
				if(min_dis + cost[nextnode][i] < distance[i]) {
					#pragma omp critical
					distance[i] = min_dis + cost[nextnode][i];
					prev[i] = nextnode;
				}
			}
		}
		count++;
	}

/*
	// print the path and distance of each node
	for(i = 0; i < rows; i++) {
		if(i != startnode) {
			printf("Distance of node %d = %d\n", i, distance[i]);
			printf("Path = %d", i);
			
			j = i;
			do { 
				j = prev[j];
				printf("<-%d", j);
			} while(j != startnode);
		}
	}
*/

}

