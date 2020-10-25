/*
Student : Melissa Chow
*/
#include <iostream>
#include <string>
using namespace std;

int main() {
	string verb, noun, timeDay, adj, greeting, noun2;
	cout << "Welcome to Mad Libs!" << endl;
	cout << "Enter a time of day: ";
	cin >> timeDay;
	cout << "Enter a verb: ";
	cin >> verb;
	cout << "Enter a noun: ";
	cin >> noun;
	cout << timeDay << " I'm " << verb << " like a(n) " << noun << "." << endl;
	cout << endl;

	cout << "Enter a noun: ";
	cin >> noun;
	cout << "Enter an adjective: ";
	cin >> adj;
	cout << "Enter a verb: ";
	cin >> verb;
	cout << "Enter a greeting: ";
	cin >> greeting;
	cout << "To be " << noun << ", to feel, " << adj << " to be " << verb << " out in the dark, " << greeting << " to my life." << endl;
	cout << endl;

	cout << "Enter a verb: ";
	cin >> verb;
	cout << "Enter a noun: ";
	cin << noun;
	cout >> "Enter an adjective: ";
	cin << adj;
	cout << "Enter another noun: "
	cin >> noun2;
	cout << "When I " << verb << " your " << noun << " it's just " << adj << noun2 << endl;

	system("pause");
}
