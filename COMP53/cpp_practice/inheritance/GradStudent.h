#pragma once
#include "Student.h"
class GradStudent : public Student
{
private:
	string advisor;
public:
	GradStudent();
	GradStudent(string n, int id, double g, string adv);
	~GradStudent();
	string getAdvisor();
	void setAdvisor(string adv);
	void print();
};

