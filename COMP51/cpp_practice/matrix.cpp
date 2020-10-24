#include <iostream>
using namespace std;

void totals(const int m[][3], int rowTotal[], int colTotal[]) {
	for (int row = 0; row < 3; row++) {
		rowTotal[row] = 0;
		for (int col = 0; col < 3; col++) {
			rowTotal[row] += m[row][col];
			// cout << "[" << row << "][" << col << "]" << sum << endl;
		}
		cout << "row [" << row << "] = " << rowTotal[row] << endl;
	}

	for (int col = 0; col < 3; col++) {
		colTotal[col] = 0;
		for (int row = 0; row < 3; row++) {
			colTotal[col] += m[row][col];
			// cout << "[" << row << "][" << col << "]" << sum << endl;
		}
		cout << "column [" << col << "] = " << colTotal[col] << endl;
	}
}

int main() {
	int matrix[3][3] = { {5, 10 ,15}, {10, 20, 30}, {1, 2, 3} };
	int rowTotal[3], colTotal[3];

	totals(matrix, rowTotal, colTotal);

	/*for (int row = 0; row < 3; row++) {
		sum = 0;
		for (int col = 0; col < 3; col++) {
			sum += matrix[row][col];
			cout << "[" << row << "][" << col << "]" << sum << endl;
		}
		cout << "row [" << row << "] = " << sum << endl;
	}

	cout << endl;
	sum = 0;
	for (int col = 0; col < 3; col++) {
		sum = 0;
		for (int row = 0; row < 3; row++) {
			sum += matrix[row][col];
			cout << "[" << row << "][" << col << "]" << sum << endl;
		}
		cout << "column [" << col << "] = " << sum << endl;
	}
	*/
	system("pause");
}