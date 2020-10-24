#pragma once
#include "Pet.h"
class Dog : 
	public Pet
{
public:
	Dog();
	~Dog();
	Dog(string n);
	string speak();
};

