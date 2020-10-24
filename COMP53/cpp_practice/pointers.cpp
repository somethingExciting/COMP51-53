#include <iostream>
using namespace std;

int main() {
	//double arr[20];
	int size;
	cout << "Enter size: ";
	cin >> size;
	double *arr = new double[size];
	double *p1, *p2;
	p1 = arr;
	//p2 = &arr[19];
	p2 = &arr[size - 1];
	size = p2 - p1;
	cout << "P1 = " << p1 << " P2 = " << p2 << " size = " << size << endl;
	cout << (p2 - p1) << endl;

	system("pause");
}