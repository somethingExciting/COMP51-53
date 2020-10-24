#include "Pet.h"
#include "Dog.h"
#include "Cat.h"

void report(Pet &pet) {
	cout << pet.speak() << endl;
}

int main() {
	//Pet p1;
	Cat c1("Garfield");
	Dog d1("Bingo");
	//cout << p1.getName() << endl;
	cout << c1.getName() << endl;
	cout << d1.getName() << endl;
	//report(p1);
	report(c1);
	report(d1);

	system("pause");
}