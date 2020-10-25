/******************************************************************
 * File: shape.cpp
 * Description: Implementation file for the Shape class, from which
 *              the Rectangle and Triangle will be derived.
 *****************************************************************/
#include <iostream>
#include "shape.h"
using namespace std;

// ***** Constructors *****
Shape::Shape()
{
	row = col = 10;
}

Shape::Shape(int r, int c)
{
	// set the row, unless row > 20
	if (r < 20)
		row = r;
	else
		row = 0;

	// set the col unless col > 70
	if (c < 70)
		col = c;
	else
		col = 0;
}

/* Function: draw( )
 * Description: Can't draw a generic shape, so it just displays a
 *              message.  Function is redefined by children.
 */
void Shape::draw()
{
	cout << "Pretend I've drawn a generic shape ...\n";
}