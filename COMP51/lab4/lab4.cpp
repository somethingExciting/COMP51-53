#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	int numYears;
	double i = 0;
	double j = 0;
	double initialBalance;
	double balance = 0;
	double interestRate1, interestRate2 = 0;

	cout.setf(ios::fixed);
	cout.precision(2);

	cout << "Please enter your initial balance: $";
	cin >> initialBalance;
	cout << "Please enter the interest rate: ";
	cin >> interestRate1;
	cout << "Please enter the amount of years you want to save for: ";
	cin >> numYears;

	balance = initialBalance;
	for (i = 0; i <= numYears; i++) {
		balance = balance * (1 + interestRate1 / 100.0);
	}
	cout << "Your balance after 4 years will be $" << balance << "." << endl;
	cout << endl;

	cout << "Let's see how different interest rates affect your balance after one year." << endl;
	cout << "Please enter the minimum and maximum interest rates: ";
	cin >> interestRate1 >> interestRate2;
	for (i = interestRate1; i <= interestRate2; i += 0.5) {
		balance = initialBalance * (1 + i / 100.0);
		cout << "$" << balance << endl;
		}





	system("pause");
}