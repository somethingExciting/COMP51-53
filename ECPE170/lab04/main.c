#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "functions.h"

int main(int argc, char *argv[]) {
	int i, y_val, nrows;
	char col_labels[20] = {"abcdefghijklmnopqrst"}, coord[10];


	setup(nrows);
	printf("do i even get here");
	int ncols = nrows;
	char **board = (char **)malloc(nrows * sizeof(char *));
	char **key = (char **)malloc(nrows * sizeof(char *));
	for(int i = 0; i < nrows; i++) {
		board[i] = (char *)malloc(ncols * sizeof(char));
		key[i] = (char *)malloc(ncols * sizeof(char));
		for(int j=0;j<nrows;j++){
			board[i][j]='-';
			key[i][j]='o';
		}
	}
	//init_board(&*board, nrows, '-');
	//init_board(&*key, nrows, 'o');


	FILE *demo;
	int counter=1, numships=0; 
	char boat_type, direction, start[3], read[200], *token;
	printf("WHY");
	//placing ships on key after reading in position from demo_file
	demo = fopen("demo.txt", "r");
	if(demo == NULL) {
		printf("Error opening file...");
		exit(0);
	}
	if(demo) {
		while(fgets(read, 10, demo) != NULL) {
			if(read[0] != '#' && strlen(read)>0) {
				//printf("read=%s", read);
				token = strtok(read, " ");
				while(token!=NULL && numships < 4) {
					//printf("\n a=%s", token);
					if(counter==1) {
						boat_type = *token;
						counter++;
					}
					else if(counter==2) {
						direction = *token;
						counter++;
					}
					else {
						strcpy(start, token);
						counter=1;
						numships++;
						place_boat(&*key, col_labels, nrows, boat_type, direction, convert_alphanum(start[0], col_labels), y_val);
					}
					token = strtok(NULL, " ");
				}

				/*if(start[2] != '0') {
					num3 = (((int)start[1]) - '0')*10 + start[2] - '0';
				else { */
					y_val = (int)start[1] - '0';
				//}
			}
			else {
				while(fgetc(demo) != '\n') {};
			}
		}
	}







	//loops until the user has reached end game
	int shots = (int)((nrows/2)*(nrows/2));
	//while((win((int)shots, numships)) == 1 || (win((int)shots, numships)) == 2) {
		printf("You have %d shots remaining\n", (int)shots);
		for(int p=0;p<10;p++) {
			coord[p] = 'n';
		}
		printf("Enter the coordinate of your shot(x,y): ");
		scanf("%c3", coord);
		int x_val = convert_alphanum(coord[0], col_labels);
		if(coord[2] != 'n') {
			y_val = (((int)coord[1] - '0')*10) + (int)coord[2] - '0';
		}
		else {
			y_val = (int)coord[1] - '0';
		}
		space_occupied(&*key, &*board, nrows, x_val, y_val);
		print_board(&*board, nrows, col_labels);
		print_board(&*key, nrows, col_labels);
	//}
	fclose(demo);

return 0;
}
