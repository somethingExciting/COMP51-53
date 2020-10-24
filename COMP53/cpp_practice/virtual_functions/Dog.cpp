#include "Dog.h"



Dog::Dog()
{
}


Dog::~Dog()
{
}


Dog::Dog(string n) : Pet(n)
{
}


string Dog::speak()
{
	return "Bark";
}
