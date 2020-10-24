#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

class Car {
public:
	Car() {
		arrivalDay = arrivalHour = ticketNum = 0;
	}
	void setCar(int day, int hour, int num) {
		arrivalDay = day;
		arrivalHour = hour;
		ticketNum = num;
	}
	int getDay() {
		return arrivalDay;
	}
	int getHour() {
		return arrivalHour;
	}
	int getTicketNum() {
		return ticketNum;
	}
private:
	int arrivalDay;
	int arrivalHour;
	int ticketNum;
};

int cost(int time) {
	int price = 0;
	switch (time) {
	case 0:
		price = 4;
		break;
	case 1:
		price = 7;
		break;
	case 2: 
		price = 10;
		break;
	case 3:
		price = 13;
		break;
	case 4:
		price = 15;
		break;
	case 5: 
		price = 17;
		break;
	case 6:
		price = 19;
		break;
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
		price = 22;
		break;
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 21:
	case 22:
	case 23:
		price = 26;
		break;
	}
	return price;
}

class ParkingLot {
public:
	void readArrivals(string txtName)  {
		inStream.open(txtName);
		while (inStream >> num >> location >> day >> hour) {
			parking[location-100].setCar(day, hour, num);
			//cout << parking[location-100].Car::getDay() << endl;
			totalCars++;
		}
		
		inStream.close();
	}

	void readPickups(string txtDoc) {
		inStream.open(txtDoc);
		while (inStream >> num >> day >> hour) {
			findCar = getCar(num);
			totalCost = calculateCost();
			remaining++;
			cout << "Ticket: " << num << ", ";
			cout << "Arrived: " << parking[findCar].Car::getDay() << ":" << setw(2) << setfill(' ') << parking[findCar].Car::getHour() << " --- ";
			cout << "Pickup: " << day << ":" << setw(2) << setfill(' ') << hour << " ------ ";
			cout << "Cost: " << totalCost << endl;
		}
		inStream.close();
	}

	int getCar(int ticket) {
		for (int i = 0; i < 50; i++) {
			if (ticket == parking[i].getTicketNum()) {
				return i;
			}
		}
	}

	int getTotalCars() {
		return totalCars - remaining;
	}

	int calculateCost() {
		if (day == parking[findCar].getDay()) {
			time1 = hour - parking[findCar].getHour();
			totalCost = cost(time1);
			totalTime += time1;
			//cout << totalCost << endl;
		}
		else if (day > parking[findCar].getDay()) {
			time1 = 24 - parking[findCar].getHour();
			time2 = hour;
			totalCost = cost(time1) + cost(time2);
			totalTime += time1 + time2;
			//cout << totalCost << endl;
		}
		revenue += totalCost;
		return totalCost;
	}

	double getRevenue() {
		return revenue;
	}

	double getAverage() {
		return (double)totalTime/remaining;
	}
private:
	ifstream inStream;
	Car parking[50];
	int totalCars, day, hour, num, location, findCar, time1, time2, totalCost, average; 
	int remaining = 0;
	int totalTime = 0;
	int revenue = 0;
};

int main() {
	ParkingLot pLot;

	pLot.readArrivals("arrivals.txt");
	cout << "Total cars arrived = " << pLot.getTotalCars() << endl;
	pLot.readPickups("pickups.txt");
	cout << "Total revenue for the period = $" << pLot.getRevenue() << endl;
	cout << "Average time stay for the period = " << pLot.getAverage() << endl;
	cout << "Total cars remaining = " << pLot.getTotalCars() << endl;
	system("pause");
}