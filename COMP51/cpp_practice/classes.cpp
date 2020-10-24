#include <iostream>
#include <string>
using namespace std;

class student {
private:
	string firstName;
	string lastName;
	int studentId;
	double gpa;
public:
	student() {
		firstName = "John";
		lastName = "Blutarski";
		studentId = 0;
		gpa = 0.0;
	}
	student(string f, string l, int id, double g) {
		firstName = f;
		lastName = l;
		studentId = id;
		gpa = 0.0;
		if (g >= 0 && g <= 4.0)
		gpa = g;
	}
	void printName() {
		cout << lastName << ", " << firstName << endl;
		cout << "GPA = " << gpa << endl;
	}
};

/*class vehicle {
	int numWheels, year, seating, doors, VIN;
	string make, model, color;
	double weight;
	bool hatchBack;
	void printCar();
	bool validateVIN();
};
*/

int main() {
	student ethan("Ethan", "Lo", 1234, 4.0), student();
	// ethan.setStudent("Ethan", "Lo" ,1234, 4.0);
	// ethan.lastName = "Lo";
	// ethan.gpa = 4.0;
	// ethan.studentId = 1234;
	ethan.printName();

	/*vehicle cars[10];
	updateCars(cars);
	if (cars[0].validateVIN()) {
		vehicle harley;
		harley.numWheels = 2;
	}
	*/
	system("pause");
}