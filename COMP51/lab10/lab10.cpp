#include <iostream>
#include <iomanip>
using namespace std;

class fraction {
private:
	int num, den;
public: 
	fraction() {
		num = 1;
		den = 2;
	}
	fraction(int n, int d) {
		num = n;
		den = d;
		if (d == 0) {
			cout << "Please enter a valid denominator.";
			exit(1);
		}
	}
	int getNum() {
		return num;
	}
	int getDen() {
		return den;
	}

	void printFraction() {
		cout << num << "/" << den << endl;
	}
	double getDecimal() {
		setprecision(3);
		double decimal = (double)num / (double)den;
		return decimal;
	}
};

int main() {
	fraction farr[3];

	fraction f1, f2(6, 10);
	f1.printFraction();
	f2.printFraction();
	farr[3];
	for (int i = 0; i < 0; i++) {

	}


	system("pause");
}