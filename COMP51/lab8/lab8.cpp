#include <iostream>
#include <fstream>
using namespace std;

void getData() {
	ofstream outStream;
	int month, score, amount;

	cout << "How many students are you entering in scores for? ";
	cin >> amount;
	cout << "Enter the month(1-12) and scores of students: " << endl;
	outStream.open("student.txt");
	if (outStream.fail()) {
		cout << "File open failed." << endl;
		exit(1);
	}
	for (int i = 0; i < amount; i++) {
		cin >> month >> score;
		outStream << month << " " << score << endl;
	}
	outStream.close();
}

void analyzeData() {
	ifstream inStream;
	int month, score, julyCount = 0, otherCount = 0, julySum = 0, otherSum = 0, julyAverage = 0, otherAverage = 0;

	inStream.open("student.txt");
	if (inStream.fail()) {  
		cout << "File open failed." << endl; 
		exit(1); 
	}
	while (inStream >> month >> score) {
	if (month == 7) {
		julySum += score;
		julyCount++;
	}
	else {
		otherSum += score;
		otherCount++;
	}
	}
	julyAverage = julySum / julyCount;
	otherAverage = otherSum / otherCount;
	cout << "Average of July scores = " << julyAverage << endl;
	cout << "Average of other month scores = " << otherAverage << endl;

	inStream.close();
}

int main()  {
	int choice;

	do {
		cout << "1) Create a new file" << endl;
		cout << "2) Append to an existing file" << endl;
		cout << "3) Analyze a data file" << endl;
		cout << "4) Quit" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			getData();
			break;
		case 2:
			cout << "Option not available" << endl;
			break;
		case 3:
			analyzeData();
			break;
		case 4:
			break;
		default:
			cout << "Please enter a valid statement." << endl;
			break;
		}
	} while (choice != 4);
	system("pause");
}