#pragma once
#include <iostream>
#include <string>
using namespace std;
class Student
{
protected:
	string name;
	int ID, size;
	double GPA;
	char *grades;
public:
	Student();
	Student(string n, int id, double g);
	~Student();
	string getName();
	int getID();
	double getGPA();
	void setName(string n);
	void setID(int id);
	void setGPA(double gpa);
	void print();
};

