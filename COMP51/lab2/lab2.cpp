#include <iostream>
#include <ctime>
using namespace std;

int main() {
	srand((unsigned)time(0));
	char choice;
	int num1;
	int num2;
	int num3;

	do {
	cout << "Welcome to my calculator!" << endl;
	     << endl;
	     << "Select an operation from the list." << endl;
	cout << "(A)dd" << endl;
	cout << "(S)ubtract" << endl;
	cout << "(M)ultiply" << endl;
	cout << "(D)ivide" << endl;
	cout << "(C)omparison" << endl;
	cout << "(R)andom" << endl;
	cout << 
	cin >> choice;
	switch (choice) {
	case 'A':
	case 'a':
		cout << "Input two numbers: ";
		cin >> num1;
		cin >> num2;
		num3 = num1 + num2;
		cout << "The sum is " << num3 << endl;
		break;
	case 'S':
	case 's':
		cout << "Input two numbers: ";
		cin >> num1;
		cin >> num2;
		num3 = num1 - num2;
		cout << "The answer is " << num3 << endl;
		break;
	case 'M':
	case 'm':
		cout << "Input two numbers: ";
		cin >> num1;
		cin >> num2;
		num3 = num1 * num2;
		cout << "The product is " << num3 << endl;
		break;
	case 'D':
	case 'd':
		cout << "Input two numbers: ";
		cin >> num1;
		cin >> num2;
		if (num2 == 0) {
			cout << "Error!";
			cout << "Cannot divide by zero!" << endl;
			return 0;
		}
		else {
			num3 = num1 / num2;
			cout << "The answer is " << num3 << endl;
		}
		break;
	case 'C':
	case 'c':
		cout << "Input two numbers: ";
		cin >> num1;
		cin >> num2;
		if (num1 > num2) {
			cout << num1 << " is greater than " << num2 << endl;
		}
		else {
			cout << num1 << " is less than " << num2 << endl;
		}
		break;
	case 'R':
	case 'r':
		cout << "Enter the range of numbers that you would like (min then max): ";
		cin >> num1;
		cin >> num2;
		cout << "The range of numbers is: " << endl;
		cout << (rand() % (num2 - num1)) << endl;
		cout << (rand() % (num2 - num1)) << endl;
		cout << (rand() % (num2 - num1)) << endl;
		cout << (rand() % (num2 - num1)) << endl;
		cout << (rand() % (num2 - num1)) << endl;
		break;
	default:
		cout << "Please enter a valid response." << endl;
		return 0;
		break;
	} while ();
}

	system("pause");
}