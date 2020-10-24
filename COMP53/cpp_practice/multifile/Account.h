#pragma once
class Account
{
public:
	Account();
	~Account();
private:
	double balance;
	double rate;
public:
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
	Account(double b, double r) {
		balance = b;
		rate = r;
	}
};

