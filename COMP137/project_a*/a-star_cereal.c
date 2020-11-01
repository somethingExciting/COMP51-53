/*
Purpose:	Simulate A* with the parallelization of Dijkstra's algorithm (since they both aim to find the shortest optimal path from point A to point B).
Compile:	gcc -g -Wall -o a-star a-star.c -lm
Run:		./a-star <number of vertices>
*/
#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>
#include <time.h>

// static variables
#define INFIN 9999

// global variables
int startnode = 0, vertices = 0, rows = 0, cols = 0;
int** cost  = NULL; // cost matrix
int* distance = NULL;
int* prev = NULL;
int* visited = NULL;

// function prototypes
void a(int** G, int rows, int cols);

/*
function: main driver 
input: argc - argument counter
	   argv - argument vector
output: N/A
*/
int main(int argc, char *argv[]) {
	srand(time(NULL));
	int** map = NULL;
	clock_t start, finish;
	int i, j;

	if (argc > 2 || argc < 0) {
		printf("Invalid amount of arguments. Input is <executable> <number of vertices>\n");
		exit(0);
	}
	vertices = atoi(argv[1]);

	rows = cols = floor(sqrt(vertices));
	
	map = (int **)malloc(rows*sizeof(int*));
	for (i = 0; i < rows; i++) {
		map[i] = (int *)malloc(cols*sizeof(int));
		for (j = 0; j < cols; j++) {
			map[i][j] = rand() % 1000;
		}
	}

	start = clock(); 
	a(map, rows, cols);
	finish = clock();

	printf("A* took %fs to execute with %d vertices\n", ((float)(finish-start)), vertices);

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
	visited = (int *)malloc(rows*sizeof(int));	// visited path
	int count = 0;								// number of nodes seen so far
	int min_dis, nextnode, i ,j;				// minimum distance, next node

	// creating memory for the cost matrix
	cost = (int **)malloc(rows*sizeof(int*));
	for(i = 0; i < rows; i++) {
		cost[i] = (int *)malloc(cols*sizeof(int));
	} 

	// creating the cost matrix 
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

	// initializing distance, prev, visited
	for (i = 0; i < rows; i++) {
		distance[i] = cost[startnode][i];
		prev[i] = startnode;
		visited[i] = 0;
	} 

	distance[startnode] = 0;
	visited[startnode] = 1;
	count = 1;

	// traverse the graph/matrix for a shorter path
	while(count < rows-1) {
		min_dis = INFIN;
		for (i = 0; i < rows; i++) {
			if(distance[i] < min_dis && !visited[i]) {
				min_dis = distance[i];
				visited[i] = i;
			}
			visited[nextnode] = 1; 
			if(!visited[i]) {
				if(min_dis + cost[nextnode][i] < distance[i]) {
					distance[i] = min_dis + cost[nextnode][i];
					prev[i] = nextnode;
				}
			}
		}
		count++;
	}

}

