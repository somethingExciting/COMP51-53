/*******************************************************************************
 * File: account.h
 * Author: E. Bowring
 * Description: Header file for a simple account class that tracks the name
 *              and account balance of an account.  Will be used as a base class
 *              to inherit from in lab 3.
 ******************************************************************************/

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>
using namespace std;

class Account
{
private:
	double balance;
protected:
	string name;
public:
	// constructors
	Account();
	Account(string n, double b);
	// accessors
	string getName();
	double getBalance();
	// mutators
	void setName(string n);
	void setBalance(double b);
	// display function
	void print();
};

// alternate display function
ostream& operator << (ostream& out, Account a);

#endif