#pragma once
#include "Account.h"
class Savings : public Account {
private:
	double rate, Balance;
public:
	Savings();
	Savings(double r, string n, double b);
	~Savings();
	void setRate(double r);
	double getRate();
	void print();
	void update();
};

