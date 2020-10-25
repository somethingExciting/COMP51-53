/****************************************************************
 * File: main.cpp
 * Description: The application file for Lab 4.
 ***************************************************************/

#include <iostream>
#include <ctime>
#include "rectangle.h"
#include "triangle.h"
using namespace std;

int main()
{
	srand(unsigned(time(0)));
	Shape* arr[4][4];
	int row, col;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int num = rand() % 2;
			if (num == 0) {
				arr[i][j] = new Triangle();
				//arr[i][j]->draw();
			}
			else {
				arr[i][j] = new Rectangle();
				//arr[i][j]->draw();
			}
		}
	}
	cout << "Enter a coordinate: ";
	cin >> row >> col;
	arr[row][col]->draw();


	/*Shape* sPtr = new Shape();
	sPtr->draw();
	Shape* sPtr = new Triangle(10, 12, 5);
	sPtr->draw();
	Shape* sPtr = new Rectangle(5, 10, 10, 5);
	sPtr->draw();*/

	//Triangle* sPtr = new Shape();
	//sPtr->draw();
	//Triangle* sPtr = new Triangle(10, 12, 5);
	//sPtr->draw();
	//Triangle* sPtr = new Rectangle(5, 10, 10, 5);
	//sPtr->draw();

	/*Rectangle* sPtr = new Shape();
	sPtr->draw();
	Rectangle* sPtr = new Triangle(10, 12, 5);
	sPtr->draw();
	Rectangle* sPtr = new Rectangle(5, 10, 10, 5);
	sPtr->draw();
*/
	system("PAUSE");
}