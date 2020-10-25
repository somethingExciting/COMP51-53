/*******************************************************************************
 * File: account.cpp
 * Author: E. Bowring
 * Description: Implementation file for a simple account class that tracks the
 *              name and account balance of an account.  Will be used as a base
 *              class to inherit from in lab 3.
 ******************************************************************************/

#include "account.h"

/***** Constructors *****/

Account::Account()
{
	name = "";
	balance = 0;
}

Account::Account(string n, double b)
{
	name = n;
	balance = b;
}

/***** Accessors *****/

string Account::getName()
{
	return name;
}

double Account::getBalance()
{
	return balance;
}

/***** Mutators *****/

void Account::setName(string n)
{
	name = n;
}

void Account::setBalance(double b)
{
	balance = b;
}

/***** Display Functions *****/

void Account::print()
{
	cout << *this;
}

ostream& operator << (ostream& out, Account a)
{
	out.setf(ios::fixed);
	out.precision(2);
	out << "Name: " << a.getName() << endl
		<< "Balance: $" << a.getBalance() << endl;
	return out;
}
