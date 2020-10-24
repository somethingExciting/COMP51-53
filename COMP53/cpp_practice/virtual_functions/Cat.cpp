#include "Cat.h"



Cat::Cat()
{
}


Cat::~Cat()
{
}


Cat::Cat(string n) : Pet(n)
{
}

string Cat::speak()
{
	return "Meow";
}
