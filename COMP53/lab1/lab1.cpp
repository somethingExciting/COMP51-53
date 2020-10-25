#include <iostream>
using namespace std;

class Account {
private:
	double balance = 0, rate = 0;
public:
	Account() {
		balance = 1300;
		rate = 0.2;
	}
	Account(double b, double r) {
		balance = b;
		rate = r;
	}
	double getBalance() {
		return balance;
	}
	double getRate() {
		return rate;
	}
	Account operator ++(int n) {
		balance = balance * (1 + rate);
		return Account(balance, rate);
	}
	Account operator <<(int n) {
		cout << balance;
	}
};

bool operator >(Account& a1, Account& a2) {
	return (a1.getBalance() > a2.getBalance());
}

int main() {
	Account a1, a2;

	a1 = Account(1000, 0.1);
	cout << "Before interest: " << a1.getBalance() << " After interest: ";
	a1++;
	cout << a1.getBalance() << endl;
	a2 = Account(2000, 0.3);
	cout << "Before interest: " << a2.getBalance() << " After interest: ";
	a2++;
	cout << a2.getBalance() << endl;

	system("pause");
}