#include "Student.h"

Student::Student()
{
	ID = 0;
	GPA = 0.0;
	name = "Jose";
}

Student::Student(string n, int id, double g) {
	name = n;
	ID = id;
	GPA = g;
	size = 4;
	grades = new char[size];
	grades[0] = 'A';
	grades[1] = 'B';
}


Student::~Student()
{
	cout << "Destructor = " << grades << endl;
	delete grades;
}


string Student::getName() 
{
	return name;
}


int Student::getID() 
{
	return ID;
}


double Student::getGPA() 
{
	return GPA;
}


void Student::setName(string n) 
{
	name = n;
}


void Student::setID(int id) 
{
	ID = id;
}


void Student::setGPA(double gpa) 
{
	GPA = gpa;
}


void Student::print()
{
	cout << name << " ID = " << ID << " GPA = " << GPA << endl;
}
