#include "Student.h"
#include "GradStudent.h"

int main() {
	Student s1("Gregg", 111222, 4.0);
	GradStudent g1("Barbara", 123456, 4.0, "Jingles");

	s1.print();
	g1.print();

	if (true) {
		Student s2("Paula", 984372, 4.0);
		s2.print();
	}

	system("pause");
}