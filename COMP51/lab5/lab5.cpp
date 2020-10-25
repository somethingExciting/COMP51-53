#include <iostream> 
#include <iomanip> 
#include <cmath> 
using namespace std;

double inflation() {
	double oldVal, newVal, inflationRate;
	cout << "Please enter the old value: ";
	cin >> oldVal;
	cout << "Enter the new value: ";
	cin >> newVal;
	inflationRate = (newVal - oldVal) / oldVal;
	return inflationRate;
}

void projection(double curPrice, double rate, int years) {
	double futurePrice;
	futurePrice = curPrice * (pow(1 + rate, years));
	cout << futurePrice;
}

void presentVal(double targetValue, double rate, int years, double &PV) {
	PV = targetValue / pow(1 + rate, years);
}

	int main() {
		int choice;  // variable to store the user's menu choice 
		double rate = 0.0; // interest rate to be used for future and present value
		double currentPrice; // current amount of money to invest 
		double targetValue = 0.0; // target amount for present value 
		double PV; 			  // present value to be calculated.
		int years; // keep displaying the menu until the user elects to quit 
		do {
		cout << "Please pick a menu option:\n" << "1) Calculate Inflation\n" << "2) Calculate Projected Price\n" << "3) Calculate the Present Value\n" << "4) Quit\n";
		cin >> choice;
		switch (choice) {
		case 1: //inflation
			rate = inflation(); 
			cout.setf(ios::fixed); 
			cout.precision(2); 
			cout << "The rate of inflation is " << rate << " or " << (rate * 100) << "%\n\n";
			break; 
		case 2: //projection
			cout << "Please enter the current price: $";
			cin >> currentPrice;
			cout << "Please enter the rate of inflation(in decimal): ";
			cin >> rate;
			cout << "Please enter the amount of years: ";
			cin >> years;
			cout << "The projected price is $";
			cout.setf(ios::fixed);
			cout.precision(2);
			projection(currentPrice, rate, years);
			cout << endl << endl;
			break; 
		case 3: // present value
			cout << "Please enter the target value: $";
			cin >> targetValue;
			cout << "Please enter the rate of inflation(in decimal): ";
			cin >> rate;
			cout << "Please enter the amount of years: ";
			cin >> years;
			cout.setf(ios::fixed);
			cout.precision(2);
			presentVal(targetValue, rate, years, PV);
			cout << "The present value is $" << PV << endl;
			cout << endl;
			break; 
		case 4: 
			break; 
		default:
			cout << "Invalid choice, please try again!\n\n";
			break;
	}
} while (choice != 4); 

system("PAUSE");
}
																																																																												   //************* INSERT PRESENT VALUE FUNCTION PLUS CODE HERE! *******************