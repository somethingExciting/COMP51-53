#include "account.h"
#include "savings.h"


int main() {
	cout << "Using a regular account" << endl;
	Account a1("Jenny", 400);
	a1.print();
	cout << endl;
	cout << "Using a savings account" << endl;
	Savings s1(0.3, "George", 500);
	for (int i = 1; i <= 10; i++) {
		cout << "After " << i << " year(s)" << endl;
		s1.update();
		s1.print();
		cout << endl;
	}

	system("pause");
}