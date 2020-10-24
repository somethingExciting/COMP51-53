#include <iostream>
#include <string>
using namespace std;

void hello(string &n) {
	n = "Hello " + n;
	// cout << "function name: " << n << endl; 
}

int main() {
	string name;

	cout << "Enter name: ";
	cin >> name;
	hello(name);
	cout << name << endl; 

	system("pause");
}