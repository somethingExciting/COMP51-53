#include <iostream>
using namespace std;

int main() {
	/*
	for (int i = 12; i < 23; i += 2) { // (i += 2) is more efficient than (i % 2 == 0) bc it skips numbers rather than executing the loop many times
		if (i % 2 == 0)
			cout << i << endl;
	}
	*/

	/*
	int fact = 1, max;

	cout << "Enter factorial size: ";
	cin >> max;
	
//	for (int i = 5; i > 0; i--) {
	for (int i = 1; i <= max; i++) {
		fact = fact * i;
		cout << i << " " << fact << endl;
	}
	cout << "Factorial 5= " << fact << endl;
	*/

	/*
	int sum = 0, num;

	for (int i = 0; i < 4; i++) {
		cout << "Enter positive number: ";
		cin >> num;
		if (num < 0) {
			cout << "Negative number" << endl;
			i--; //dangerous to mess with varaibles inside the for loop
			// break;
			continue;
		}
		sum = sum + num;
	}
	cout << "Sum = " << sum << endl;
	*/

	for (int i = 1; i <= 4; i++) {
		for (int j = 0; j < i; j++) {
			cout << i;
		}
		cout << endl;
	}


	system("pause");
}