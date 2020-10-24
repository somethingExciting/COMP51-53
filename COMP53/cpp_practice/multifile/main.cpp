#include <iostream>
#include "Account.h"
using namespace std;

bool operator >(Account &a1, Account &a2) {
	return (a1.getBalance() > a2.getBalance());
}

int main() {
	Account a1;
	cout << a1.getBalance() << endl;

	system("pause");
}