#include <iostream>
using namespace std;

int main() {
	int rank;
	
	cout << "Enter your performance ranking: ";
	cin >> rank;
	switch (rank) {
	case 5:
		cout << "You have exceeded all objectives." << endl;
		break;
	case 4:
		cout << "You have exceeded most objectives." << endl;
		break;
	case 3:
	case 2:
		cout << "You have met objectives." << endl;
		break;
	case 1:
		cout << "You do not meet the objectives. You're fired!" << endl;
		break;
	default:
		cout << "Invalid ranking!" << endl;
	}
	system("pause");
}