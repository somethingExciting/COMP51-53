#include <stdlib.h>
#include <stdio.h>	   // Input and output
#include <stdint.h>	   // Use uint32_t
#include <stdbool.h>   // Use bool as a datatype
#include <string.h>    // For string comparison
#include <time.h>	   // Get time
#include <inttypes.h>

#include "lab12.h"


uint32_t m_w = 50000;
uint32_t m_z = 60000;
int rows = 6, cols = 9;
char board[6][9];

// Generate random number in range [low, high]
// (i.e. including low and high)
uint32_t random_in_range(uint32_t low, uint32_t high)
{
  uint32_t range = high-low+1;
  uint32_t rand_num = get_random();

  return (rand_num % range) + low;
}


// Generate random 32-bit unsigned number
// based on multiply-with-carry method shown
// at http://en.wikipedia.org/wiki/Random_number_generation
uint32_t get_random()
{
  uint32_t result;
  m_z = 36969 * (m_z & 65535) + (m_z >> 16);
  m_w = 18000 * (m_w & 65535) + (m_w >> 16);
  result = (m_z << 16) + m_w;  /* 32-bit result */

  return result;
}


//prints board
void print_board(bool init)
{
	printf("\n   1 2 3 4 5 6 7 \n");
	for(int i=0; i < rows; i++) 
	{
		for(int j=0; j < cols; j++) 
		{
			if(init) {
				board[i][j] = '-';
			}
			if((j == 0 || j == 8) && (i%2==1)) {
				board[i][j] = 'H';
			}
			if((j == 0 || j == 8) && (i%2==0)) {
				board[i][j] = 'C';
			}
			printf(" %c", board[i][j]);
		}
		printf("\n");
	}
}


//checks if a win or loss has occurred
int win() 
{
	for(int i=0; i < rows; i++) 
	{
		for(int j=0; j < cols; j++) 
		{
			if(board[i][j] != '-') 
			{

				//checks top-down diagonal
				if((i+4) < rows && (j+4) < cols) {
					if(board[i][j] == board[i+1][j+1] && board[i+1][j+1] == 						board[i+2][j+2] && board[i+2][j+2] == board[i+3][j+3] && 							board[i+3][j+3] == board[i+4][j+4]) {
//printf("top-down diagonal");						
						return 1;
					}
				}


				//checks bottom-up diagonal
				if((i+4) < rows && (j-4) >= 0) {
					if(board[i][j] == board[i+1][j-1] && board[i+1][j-1] == 						board[i+2][j-2] && board[i+2][j-2] == board[i+3][j-3] && 							board[i+3][j-3] == board[i+4][j-4] ) {
//printf("bottom-up diagonal");						
						return 1;
					}

				}


				//checks horizontal 
				if((j+4) < cols) {
					if(board[i][j] == board[i][j+1] && board[i][j+1] == board[i][j+2] 							&& board[i][j+2] == board[i][j+3] && board[i][j+3] == 							board[i][j+4]) {
//printf("horizontal");
						return 1;
					}
				}


				//checks vertical
				if((i+4) < rows) {
					if(board[i][j] == board[i+1][j] && board[i+1][j] == board[i+2][j] 							&& board[i+2][j] == board[i+3][j] && board[i+3][j] == 							board[i+4][j]) {
//printf("vertical");						
						return 1;
					}
				}

			//endif != -
			}
		//endfor cols 
		}
	//endfor rows
	}
	return 0;
}


//places the piece on the board 
void place_on_board(char space, int col_choice)
{
	int currow = rows-1, y; 

	while(1) {
		if(board[currow][col_choice] != '-') {
			currow--;
		}
		else {
			board[currow][col_choice] = space; 
			break;
		}

		if(currow < 0 || col_choice > 7 || col_choice < 1) {
			if(space == 'H') {
				printf("Invalid move, select another column: ");
				scanf("%d", &y);
				place_on_board(space, y);
			}
			else {
				place_on_board(space, (col_choice%9)+1);
			}
			break;
		}

	}	

}


//checks if a tie has occurred
int check_tie(int win)
{
	int counter = 0;

	if(win == 0) {
		for(int i=0; i < rows; i++) {
			for(int j=0; j < cols; j++) {
				if(board[i][j] == '-') {
					break;
				}
				else {
					counter++;
					if(counter == 52) {
						printf("Tie\n");
						return 1;
					}
				}
			}
		
		}
	}
	return 0;

}


int main(int argc, char *argv[]) 
{
	//initialize variables
	srand(time(0));
	int y;
	uint32_t num1, num2, decideTurn, compCol;
	bool playerTurn; 


	printf("Welcome to Connect-5!\n");


	//decide whether computer or human goes first
	printf("Enter 2 positive numbers to intialize the random number generator.\n");
	while(1) { 	
		printf("Number 1: ");
		scanf("%" SCNd32, &num1);
		if(num1 > 0) {
			break;
		}
		printf("Invalid value, try again.\n");
	}
	while(1) {
		printf("Number 2: ");
		scanf("%" SCNd32, &num2);
		if(num2 > 0) {
			break;
		}
		printf("Invalid value, try again.\n");
	}
	if(num1 > num2) {
		uint32_t temp; 
		temp = num2;
		num2 = num1;
		num1 = temp;
	}	
	decideTurn = random_in_range(num1, num2); 
	printf("Human player = H\n");
	printf("Computer player = C\n");
	printf("Coin toss...");
	if(decideTurn%2 == 0) {
		printf("You go first!");
		playerTurn = true;
	} else {
		printf("Computer goes first.");
		playerTurn = false;
	}


	//intializing board
	print_board(true);


	//loop until either user or computer wins game
	while(1)
	{
		if(playerTurn == true) {
			while(1) {
				printf("Enter a column number(1-7): ");
				scanf("%d", &y);
				if(y > 0) {
					break;
				}
				printf("Invalid value, try again.\n");
			}
			place_on_board('H', y);
			playerTurn = false;

			if((win()) == 1) {
				print_board(false);
				printf("\nYou win!\n ");
				break;
			}
		} else {
			num1 = 1; 
			num2 = 7;
			compCol = random_in_range(num1, num2);
			printf("Computer selected column %d", (int)compCol);
			place_on_board('C', (int)compCol);
			printf("\n");
			print_board(false);
			playerTurn = true;
			if(win()) {
				printf("You lose...\n");
				break;
			}
		}
		if((check_tie(win())) == 1) {
			break;
		}
	}

} 
