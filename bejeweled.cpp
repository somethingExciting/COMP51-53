//Melissa Chow
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <Windows.h>
using namespace std;

class Board {
private:
	int score = 0, row, col, row2, col2, num;
	char board[8][8];
	string fileName;
	ifstream inStream;
	char agree;
	bool winner = false, match = false, create = true;
	int colors[8][8];
public:
	//uses file as initialized board
	void test() {
		cout << "Would you like to test run? ";
		cin >> agree;
		if (agree == 'y' || agree == 'Y') {
			do {
				create = false;
				cout << "What file would you like to open?  ";
				cin >> fileName;
				inStream.open(fileName); //bejeweledboard.txt
				if (inStream.fail()) {
					cout << "Enter a valid file name." << endl;
				}
			} while (inStream.fail());
			for (row = 0; row < 8; row++) {
				for (col = 0; col < 8; col++) {
					//board[row][col] = 254;
					inStream >> colors[8][8];
					do {
						printBoard();
						while (checkJewels() != false);
						move();
						gameOver();
						system("CLS");
					} while (getMatch() != false);
				}
			}
		}
		else {
			return;
		}
	}
	//generates random colors to be printed onto the board
	void createBoard() {
		for (row = 0; row < 8; row++) {
			for (col = 0; col < 8; col++) {
				board[row][col] = 254;
				num = rand() % 8 + 1;
				colors[row][col] = num;
			}
		}
	}
	//determines whether the game is in a stalemate
	void gameOver() {
		for (row = 0; row < 8; row++) {
			for (col = 0; col < 8; col++) {
				if (colors[row][col] == colors[row][col + 1] && colors[row][col] != colors[row + 1][col] &&
					colors[row][col + 1] != colors[row][col] && colors[row][col] != colors[row - 1][col] &&
					colors[row][col] != colors[row][col - 1]) {
					cout << "You lose" << endl;
				}
			}
		}
	}
	//moves gems down
	void moveJewels(int r, int c) {
		while (r != 0) {
			colors[r][c] = colors[r - 1][c];
			r--;
		}
		num = rand() % 8 + 1;
		colors[0][c] = num;
	}
	//determines if there is a 3,4,or 5 in a row match
	bool checkJewels() {
		match = false;
		for (row = 0; row < 8; row++) {
			for (col = 0; col < 8; col++) {
				if (col + 2 < 8 && colors[row][col] == colors[row][col + 1] && colors[row][col] == colors[row][col + 2]) {
					moveJewels(row, col);
					moveJewels(row, col + 1);
					moveJewels(row, col + 2);
					score += 10;
					match = true;
					cout << "Found match of 3" << endl;
					if (col + 3 < 8 && colors[row][col] == colors[row][col + 3]) {
						moveJewels(row, col);
						moveJewels(row, col + 1);
						moveJewels(row, col + 2);
						moveJewels(row, col + 3);
						score += 10;
						match = true;
						cout << "Found match of 4" << endl;
						if (col + 4 < 8 && colors[row][col] == colors[row][col + 4]) {
							moveJewels(row, col);
							moveJewels(row, col + 1);
							moveJewels(row, col + 2);
							moveJewels(row, col + 3);
							moveJewels(row, col + 4);
							score += 10;
							match = true;
							cout << "Found match of 5" << endl;
							return match;
						}
						return match;
					}
					return match;
				}
				if (row + 2 < 8 && colors[row][col] == colors[row][col] && colors[row][col] == colors[row + 1][col] && colors[row][col] == colors[row + 2][col]) {
					moveJewels(row, col);
					moveJewels(row + 1, col);
					moveJewels(row + 2, col);
					score += 10;
					cout << "Found match of 3" << endl;
					match = true;
					if (row + 3 < 8 && colors[row][col] == colors[row + 3][col]) {
						moveJewels(row, col);
						moveJewels(row + 1, col);
						moveJewels(row + 2, col);
						moveJewels(row + 3, col);
						score += 10;
						cout << "Found match of 4" << endl;
						match = true;
						if (row + 4 < 8 && colors[row][col] == colors[row + 4][col]) {
							moveJewels(row, col);
							moveJewels(row + 1, col);
							moveJewels(row + 2, col);
							moveJewels(row + 3, col);
							moveJewels(row + 4, col);
							score += 10;
							cout << "Found match of 5" << endl;
							match = true;
							return match;
						}
						return match;
					}
					return match;
				}
			}
		}
	}
	//displays the board
	void printBoard() {
		cout << "   0 1 2 3 4 5 6 7" << endl;
		cout << "  ----------------" << endl;
		for (row = 0; row < 8; row++) {
			cout << row << "| ";
			for (col = 0; col < 8; col++) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colors[row][col]);
				cout << board[row][col] << " ";
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			cout << endl;
		}
	}
	//determines if the user has won
	bool win(int score) {
		if (score >= 500) {
			winner = true;
			return winner;
		}
		else {
			return winner;
		}
	}
	//verifies number input 
	void numValidation(int r, int c) {
		if ((r < 0 || r > 8) || (c < 0 || c > 8)) {
			cout << "Please enter a valid move." << endl;
		}
	}
	//verifies whether a move can be made
	bool moveValidation(int r1, int c1, int r2, int c2) {
		if (colors[row][col] == colors[row][col + 1] && colors[row][col] != colors[r1][c1]) {
			cout << "Invalid move" << endl;
			return false;
		}
		if (colors[row + 1][col] == colors[row][col] && colors[row][col] != colors[r2][c2]) {
			cout << "Invalid move" << endl;
			return false;
		}
	}
	//swaps the gems that the user has selected
	void move() {
		int temp;
		cout << "Current score: " << score << endl;
		cout << "Enter move in row-col(row[space]column) format." << endl;
		do {
			cout << "Enter first item to swap: ";
			cin >> col >> row;
			numValidation(row, col);
		} while ((row < 0 || row > 8) || (col < 0 || col > 8));
		do {
			cout << "Enter the item to swap with: ";
			cin >> col2 >> row2;
			numValidation(row2, col2);
		} while ((row2 < 0 || row2 > 8) || (col2 < 0 || col2 > 8));
		moveValidation(row, col, row2, col2);
		if (moveValidation(row,col, row2, col2) == false) {
			cout << "Please enter a valid swap." << endl;
			colors[row][col] = colors[row2][col2];
		}
		temp = colors[col][row];
		colors[col][row] = colors[col2][row2];
		colors[col2][row2] = temp;
		winner = win(score);
		if (winner == true) {
			cout << "You win!" << endl;
		}
	}
	bool getWinner() {
		return winner;
	}
	bool getMatch() {
		return match;
	}
	bool getCreate() {
		return create;
	}
};

int main() {
	srand(unsigned(time(0)));
	Board board;

	cout << "Welcome to Bejeweled!" << endl;
	board.test();
	board.createBoard();
	while (board.getWinner() == false) {
		do {
			board.printBoard();
			while (board.checkJewels() == true);
			board.move();
			//board.gameOver();
			system("CLS");
		} while (board.getMatch() != false);
	}

	system("pause");
}