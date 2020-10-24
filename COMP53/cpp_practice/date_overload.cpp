#include <iostream>
#include <cstdlib> //for exit
using namespace std;

class DayOfYear
{
public:
	DayOfYear(int monthValue, int dayValue);
	//Initializes the month and day to arguments.

	DayOfYear(int monthValue);
	//Initializes the date to the first of the given month.

	DayOfYear();
	//Initializes the date to January 1.

	void input();
	void output();
	int getMonthNumber();
	//Returns 1 for January, 2 for February, etc.
	int getDay();
	DayOfYear operator ++(int n);

private:
	int month;
	int day;
	void testDate();
};

const DayOfYear operator +(const DayOfYear &day1, const DayOfYear &day2) {
	int month = 0;
	int day = day1.getDay() + day2.getDay();
	if (day > 30) {
		day = day - 30;
		month++;
	}
	month += day1.getMonthNumber() + day2.getMonthNumber();
	if (month > 12) {
		month = month - 12;
	}
	return DayOfYear(month, day);
}


int main()
{
	DayOfYear date1(2, 21), date2(5), date3, date4;
	cout << "Initialized dates:\n";
	date1.output(); cout << endl;
	date2.output(); cout << endl;
	date3.output(); cout << endl;
	date4 = date1 + date3;
	date4.output(); cout << endl;

	system("pause");
	return 0;
}

DayOfYear DayOfYear::operator ++(int n);

DayOfYear::DayOfYear(int monthValue, int dayValue)
: month(monthValue), day(dayValue)
{
	testDate();
}

DayOfYear::DayOfYear(int monthValue) : month(monthValue), day(1)
{
	testDate();
}

DayOfYear::DayOfYear() : month(1), day(1)
{/*Body intentionally empty.*/
}

//uses iostream and cstdlib:
void DayOfYear::testDate()
{
	if ((month < 1) || (month > 12))
	{
		cout << "Illegal month value!\n";
		system("pause");
		exit(1);
	}
	if ((day < 1) || (day > 31))
	{
		cout << "Illegal day value!\n";
		system("pause");
		exit(1);
	}
}

int DayOfYear::getMonthNumber()
{
	return month;
}

int DayOfYear::getDay()
{
	return day;
}

//Uses iostream and cstdlib:
void DayOfYear::input()
{
	cout << "Enter the month as a number: ";
	cin >> month;
	cout << "Enter the day of the month: ";
	cin >> day;
	if ((month < 1) || (month > 12) || (day < 1) || (day > 31))
	{
		cout << "Illegal date! Program aborted.\n";
		system("pause");
		exit(1);
	}
}

void DayOfYear::output()
{
	switch (month)
	{
	case 1:
		cout << "January "; break;
	case 2:
		cout << "February "; break;
	case 3:
		cout << "March "; break;
	case 4:
		cout << "April "; break;
	case 5:
		cout << "May "; break;
	case 6:
		cout << "June "; break;
	case 7:
		cout << "July "; break;
	case 8:
		cout << "August "; break;
	case 9:
		cout << "September "; break;
	case 10:
		cout << "October "; break;
	case 11:
		cout << "November "; break;
	case 12:
		cout << "December "; break;
	default:
		cout << "Error in DayOfYear::output. Contact software vendor.";
	}

	cout << day;
}






