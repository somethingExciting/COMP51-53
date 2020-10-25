/**********************************************************************
 * File: rectangle.cpp
 * Description: Implementation file for the Rectangle class, which
 *              is derived from the Shape class and is used to display
 *              rectangles of stars on the screen.
 *********************************************************************/

#include "rectangle.h"
#include <iostream>
using namespace std;

// ***** Constructors *****
Rectangle::Rectangle() : Shape()
{
	height = width = 3;
}

Rectangle::Rectangle(int r, int c, int h, int w) : Shape(r,c)
{
	// set height, unless it will run off the screen
	if (h + row < 20)
		height = h;
	else
		height = 20 - row;

	// set width, unless it will run off the screen
	if (w + col < 70)
		width = w;
	else
		width = 70 - col;
}

/* Function: draw()
 * Description: Displays a rectangle at the specified location
 *              on the screen.
 */
void Rectangle::draw()
{
	// clear the screen
	system("CLS");

	int r = 0; // keeps track of rows
	// move down the appropriate number of rows
	for (; r < row; r++)
		cout << endl;
	// print col spaces and then width stars on each row to
	// form a rectangle at the appropriate location
	for (; r < row + height; r++)
	{
		for (int c = 0; c < col + width; c++)
		{
			// move across col spaces
			for (;c < col; c++)
				cout << " ";
			// print line of a rectangle
			cout << "*";
		}
		cout << endl;
	}
	// move cursor to bottom of screen.
	for (; r < 20; r++)
		cout << endl;
}