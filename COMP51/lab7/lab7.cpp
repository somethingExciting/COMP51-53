#include <iostream>
using namespace std;

void printBoard(char board[][3]) {
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			cout << board[r][c];
		}
		cout << endl;
	}
}

bool isFilled(char board[][3], int row, int col) {
	bool filled;

	if (board[row][col] == 'e') {
		filled = false;
	}
	else {
		filled = true;
	}
	return filled;
}

void move(char board[][3], char player) {
	int row, col;

	do {
		cout << "Player " << player << ":Please enter the coordinates of your move (row col): ";
		cin >> row >> col;
	} while (isFilled(board, row, col));
	board[row][col] = player;
}

bool isGameOver(char board[][3]) {


	for (int r = 0; r < 3; r++) {
		if (board[r][0] == board[r][1] && board[r][0] == board[r][2]) {
			return false;
		}
	}
	for (int c = 0; c < 3; c++) {
		if (board[c][0] == board[c][1] && board[c][0] == board[c][2]) {
			return false;
		}
	}
	if (board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
		return false;
	}
	if (board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
		return false;
	}
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (board[row][col] == 'e') {
				return true;
			}
		}
	}
	return false;
}


int main() {
	char board[3][3];
	bool xTurn = true;

	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			board[row][col] = 'e';
		}
	}
	do {
		if (xTurn) {
			move(board, 'X');
			xTurn = false;
		}
		else {
			move(board, 'O');
			xTurn = true;
		}
		printBoard(board);
		cout << endl;
	} while (!isGameOver(board));

	system("pause");
}