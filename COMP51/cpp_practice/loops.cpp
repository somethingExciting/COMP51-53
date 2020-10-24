#include <iostream>
#include <string>
using namespace std;

int main() {
	/*
	int i, items, cals, total = 0;

	cout << "Enter number of items for lunch: ";
	cin >> items;
	// i = 1;
	while (items > 0) {
		// cout << "Enter calories for item " << i << ": ";
		cout << "Enter calories for item " << items << ": ";
		cin >> cals;
		total = total + cals;
		// i++;
		items--;
	}
	cout << "Total calorie intake = " << total << endl;


	char answer;
	int count = 0;

	do {
		cout << "Are you tired yet? : ";
		cin >> answer;
		count++;
	} while (answer == 'N');
	cout << "Total pushups = " << count << endl;
	

	int num = 1;
	int count = 0;
	while (num >= 1 && num <= 100) {
		cout << "Enter a number between 1 and 100: ";
		cin >> num;
		if (num % 2 == 0) {
			cout << "That number is even." << endl;
			count++;
		}
		else {
			cout << "That number is odd." << endl;
		}
	}
	cout << "Count of even numbers = " << count << endl;
	*/


	string word;
	int count = 0;
	bool match = false;

	do {
		cout << "Enter a word. Type exit to stop. ";
		cin >> word;
		if (word == "exit") {
			cout << "Exiting the loop" << endl;
			match = true;
		}
		else {
			count = count + word.length();
		}
	} while (!match && count < 20);
	cout << "Total letters entered = " << count << endl;

	system("pause");
}