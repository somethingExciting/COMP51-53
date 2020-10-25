#include <iostream>
using namespace std;

void find(char letters[], int size, char c) {
	bool found = false;
	for (int i = 0; i < size; i++) {
		if (letters[i] == c) {
			cout << "Found " << c << " at position " << i << endl;
			found = true;
		}
	}
	if (found == false) {
		cout << c << " is not found.";
	}
}

int main() {
	int i;
	char letter;
	int result;
	const int SIZE = 8;
	char letters[8];
	for (i = 0; i < 8; i++) {
		cout << "Please enter letter #" << i << ": ";
		cin >> letter;
		letters[i] = letter;
	}
	cout << endl;
	cout << "Word is: ";
	for (i = 0; i < 8; i++) {
		cout << letters[i];
	}
	cout << endl;
	cout << "The word backwards is: ";
	for (i = 7; i >= 0; i--) {
		cout << letters[i];
	}
	cout << endl;
	cout << "What letter would you like to search for? ";
	cin >> letter; 
	find(letters, SIZE, letter);

	system("pause");
}