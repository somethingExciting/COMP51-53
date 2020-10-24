#pragma once
#include<iostream>
#include <string>
using namespace std;

class Pet
{
public:
	Pet();
	~Pet();
protected:
	string name;
public:
	Pet(string n);
	string getName();
	virtual string speak() = 0; //pure virtual function
};

