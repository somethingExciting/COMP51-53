#include "GradStudent.h"



GradStudent::GradStudent()
{
	advisor = "PowerCat";
}

GradStudent::GradStudent(string n, int id, double g, string adv) : Student(n, id, g) {
	advisor = adv;
}


GradStudent::~GradStudent()
{
}


string GradStudent::getAdvisor()
{
	return advisor;
}


void GradStudent::setAdvisor(string adv)
{
	advisor = adv;
}


void GradStudent::print()
{
	//cout << name << " ID = " << ID << " GPA = " << GPA;
	Student::print();
	cout << "Advisor = " << advisor << endl;
}
