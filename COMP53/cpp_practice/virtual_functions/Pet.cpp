#include "Pet.h"



Pet::Pet()
{
	name = "none";
}


Pet::~Pet()
{
}


Pet::Pet(string n)
{
	name = n;
}


string Pet::getName()
{
	return name;
}


string Pet::speak()
{
	return "???";
}
