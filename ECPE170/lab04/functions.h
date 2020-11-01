#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void init_board(char **board, int nrows, char hit);
void print_board(char **board, int n, char *col_labels);
int win(int shots, int ships_rekt);
void space_occupied(char **key, char **board, int n, int x, int y);
void place_boat(char **key, char *cols, int n, char type, char direction, int x, int y);
int convert_alphanum(char x, char *cols);
void setup(int nrows);

typedef enum {CARRIER, BATTLESHIP, FRIGATE} ship_type;  

typedef struct {
	int length;
	bool isVertical;
	ship_type type; 
}ship;

#endif
