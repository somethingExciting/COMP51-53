#include <iostream>
#include <string>
#include "Pair.h"
#include "Pair.cpp" //with templates, inlcude .cpp so the compiler knows where to assign the data types
using namespace std;

template<class T>
T sumArray(T arr[], int size) {
	T sum = 0;
	for (int i = 0; i < size; i++) {
		sum += arr[i];
	}
	return sum;
}

template<class T>
T addUp(Pair<T> thePair) {
	T sum = thePair.getFirst() + thePair.getSecond();
	return sum;
}

template<class T>
int compare(Pair<T> thePair) {
	if (thePair.getFirst() == thePair.getSecond()) {
		return 0;
	}
	else if (thePair.getFirst() > thePair.getSecond()) {
		return 1;
	}
	else {
		return 2;
	}
}


int main() {
	//int iArr[3] = { 5, 10, 15 };
	//cout << sumArray(iArr, 3) << endl;
	//double dArr[3] = { 1.5, 2.5, 3.5 };
	//cout << sumArray(dArr, 3) << endl;
	//bool bArr[3] = { true, false, true }; //is there any false statement
	//cout << sumArray(dArr, 3) << endl;
	//char cArr[3] = { 'a', 'b', 'c' }; //adds ascii values
	//cout << sumArray(cArr, 3) << endl;

	Pair<int> iPair(3, 2);
	cout << addUp(iPair) << endl;
	cout << compare(iPair) << endl;
	Pair<double> dPair(2.5, 3.25);
	cout << addUp(dPair) << endl;
	cout << compare(dPair) << endl;

	system("pause");
}