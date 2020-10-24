#include "Account.h"



Account::Account()
{
	balance = 0.0;
	rate = 0.0;
}


Account::~Account()
{
}


double Account::getBalance()
{
	return balance;
}


double Account::getRate()
{
	return rate;
}


Account::Account(double b, double r)
{
}
