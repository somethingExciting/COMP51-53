#pragma once
#include "Pet.h"
class Cat :
	public Pet
{
public:
	Cat();
	~Cat();
	Cat(string n);
	string speak();
};
