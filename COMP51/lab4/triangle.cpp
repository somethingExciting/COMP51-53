/****************************************************************
 * File: triangle.cpp
 * Description: Implementation file for the Triangle class, which
 *              is derived from the Shape class and is used to
 *              display triangles of stars on the screen.
 ***************************************************************/

#include "triangle.h"
#include <iostream>
using namespace std;

// ***** Constructors *****
Triangle::Triangle() : Shape()
{
	width = 3;
}

Triangle::Triangle(int r, int c, int w) : Shape(r,c)
{
	// set width, unless it will run off the screen
	if (w + col < 70)
		width = w;
	else
		width = 70 - col;
}

/* Function: draw()
 * Description: Displays a triangle at the specified location
 *              on the screen.
 */
void Triangle::draw()
{
	// clear the screen
	system("CLS");

	// move down the appropriate number of rows
	for (int r = 0; r < row; r++)
		cout << endl;
	// print col spaces and then up to width stars on each row to
	// form a triangle at the appropriate location
	for (int r = 0; r < width; r++)
	{
		for (int c = 0; c < col + width - r; c++)
		{
			// move across col spaces
			for (;c < col; c++)
				cout << " ";
			// print line of a triangle
			cout << "*";
		}
		cout << endl;
	}
	// move cursor to bottom of screen.
	for (int r = row + width; r < 20; r++)
		cout << endl;
}