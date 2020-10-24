#include <iostream>
using namespace std;

void truncate(double s[], double t[], int size) {
	for (int i = 0; i < size; i++) {
		t[i] = floor(s[i]);
	}
}

int main() {
	double source[3] = { 2.5, 3.14, 1.9 };
	double target[3];

	truncate(source, target, 3);
	for (int i = 0; i < 3; i++) {
		cout << "source[" << i << "] = " << source[i] << endl;
 		cout << "target[" << i << "] = " << target[i] << endl;
	}

	/*void isBig (bool s[]) { //in a function, the array doesn't have to be defined
	int size;
	for (int i = 0; i < 50; i++) {
		cout << "Enter size"
		cin >> size;
		if (size > 100000) {
			s[i] = true;
		} else {
			s[i] = false;
		}
	}
	*/

	system("pause");
}