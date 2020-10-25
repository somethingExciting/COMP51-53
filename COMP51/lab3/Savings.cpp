#include "Savings.h"

Savings::Savings() {
	rate = 0.1;
}
Savings::Savings(double r, string n, double b) : Account(n, b) {
	rate = r;
	name = n;
	Balance = b;
}
void Savings::setRate(double r) {
	rate = r;
}
double Savings::getRate() {
	return rate;
}
void Savings::print() {
	Account::print();
}
void Savings::update() {
	Balance = Account::getBalance() * (1 + rate);
	Account::setBalance(Balance);
}

Savings::~Savings()
{
}
