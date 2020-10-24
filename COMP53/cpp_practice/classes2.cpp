#include <iostream>
#include <string>
using namespace std;

class Owner {
private:
	string name, address, city, state, zip;
	int age;
	bool eyeRestriction;
public:
	Owner() {
		name = "John Smith";
		age = 16;
		eyeRestriction = false;
	}
	Owner(string n, int a, bool r) {
		name = n;
		age = a;
		eyeRestriction = r;
	}
	void print() {
		cout << name << " " << age;
		if (eyeRestriction) {
			cout << " Must wear glasses";
		}
		cout << endl;
	}
};

class vehicle {
private:
	string VIN, make, model;
	int gasTank, doors;
	double mpg;
	Owner owner;

	/*void setCar() {
		VIN = "123abc456";
		make = "Chevy";
		model = "Camaro";
		gasTank = 20;
		doors = 2;
		mpg = 0;
	}*/
public: 
	vehicle() {
		make = "Ford";
		model = "F150";
		VIN = "000000";
		gasTank = 20;
		doors = 2;
		mpg = 0;
		//owner = Owner();
	}
	vehicle (string v, string m, string mod, int t, int d, string n) {
		VIN = v;
		make = m;
		model = mod;
		if (t > 0) {
			gasTank = t;
		}
		else {
			t = 1;
		}
		doors = d;
		owner = Owner(n, 21, true);
		mpg = 0;
	}
	void printCar() {
		cout << make << " " << model << " VIN = " << VIN << endl;
		cout << "MPG = " << mpg << endl;
		owner.print();
	}
	void setMPG(int miles) {
		if (miles <= 0) {
			cout << "Invalid miles = " << miles << endl;
			return;
		}
		mpg = (double) miles / gasTank;
	}
};

int main() {
	vehicle camaro("123abc456", "Chevy", "Camaro", 20, 2, "Jose"), mustang("567xyz890", "Ford", "Mustang", 16, 4, "Mary"), challenger;

	//camaro.mpg() = 10;
	//camaro.setCar;
	camaro.setMPG(300);
	camaro.printCar();
	//mustang.setCar;
	mustang.setMPG(200);
	mustang.printCar();
	challenger.printCar();

	system("pause");
}