#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct inventory { //creating a data type
	string prodId;
	string prodDescr;
	double cost;
	int qty;
};

int main() {
	ifstream inStream; 
	ofstream outStream; 
	double value;
	/* double cost; 
	int qty; 
	string prodId, prodDescr;
	*/
	inventory items; // define, allocates memory for it now

	inStream.open("inventorycount.txt");
	if (inStream.fail()) {
		cout << "Cannot open file" << endl;
		system("pause");
		return 0;
	}
	outStream.open("inventoryvalue.txt");
	while (inStream >> items.prodId >> items.prodDescr >> items.cost >> items.qty) {
	value = items.cost * items.qty;
	outStream << items.prodId << " " << value << endl;;
	}
	inStream.close();
	outStream.close();

	system("pause");
}