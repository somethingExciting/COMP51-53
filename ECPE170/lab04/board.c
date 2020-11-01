#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "functions.h"

void setup(int nrows) 
{
	printf("WELCOME TO FRIGATE!\n");
	printf("Enter the size of the board(5-20): ");
	scanf("%d", &nrows);
	if(nrows < 5) {
		printf("Minimum grid size is 5... creating a board of size 5...\n");
		nrows = 5;
	}
	else if(nrows > 20) {
		printf("Maximum grid size is 20... creating a board of size 5...\n");
		nrows = 5;
	}
	else {
		printf("Creating board of size %d\n", nrows);
	}
printf("hello?");
}

//initializes board
void init_board(char **board, int n, char hit) 
{
	int i, j, k;

	for(i = 0; i < n; i++) {
		for(j=0; j < n; j++) {
			board[i][j] = hit;
		}
	}
}

//prints board
void print_board(char **board, int n, char *col_labels) 
{

	printf(" ");
	for(int k=0;k<n;k++) {
		printf(" %c ", col_labels[k]);
	}
	for(int i = 0; i < n; i++) {
		printf("%d", i);
		for(int j = 0; j < n; j++) {
			printf(" %c ", board[i][j]);
		}
		printf("\n");
	}
}

//swaps alpha w/ num if in wrong order, converts letter to num
int convert_alphanum(char x, char *cols) 
{
	for(int i=0;i<20;i++) {
		if(cols[i] == x) {
			return i;
		}
	}
}

//places ship on key
void place_boat(char **key, char *cols, int n, char type, char direction, int x, int y) 
{
	int i,j, l, length;

	if(type == 'c') {
		length = 4;
	}
	if(type == 'b') {
		length = 5;
	}
	if(type == 'f') {
		length = 2;
	}

	
	if(direction == 'r') { 
		for(i=0;i<length;i++) {
			key[x][y + i] = type; 
		}
	}
	else {
		for(i=0;i<length;i++) {
			key[x + i][y] = type; 
		}
	}
}

//checks if a space is occupied or not
void space_occupied(char **key, char **board, int n, int x, int y) 
{
	if(key[x][y] != 'o') {
		board[x][y] = 'h';
	}
	else {
		board[x][y] = 'm';
	}
}

//win if all ships are destroyed; shots > 0
//lose if shots = 0 and/or not all ships are destroyed
int win(int shots, int ships_rekt) 
{
	if(shots<=0 && ships_rekt < 4) {
		printf("You lose");
		printf("Ships sunk: %d", ships_rekt);
		return 1;
	}
	if(ships_rekt >= 4) {
		printf("You win!");
		return 2;
	}
	return 0;
}
