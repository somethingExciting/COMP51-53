/************************************************************
 * File: rectangle.h
 * Description: Header file for the Rectangle class, which
 *              is derived from the Shape class and is used
 *              to display rectangles of stars on the screen.
 ***********************************************************/

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape
{
protected:
	// inherits location of the rectangle from parent
	// size of the rectangle in stars.
	int height;
	int width;
public:
	Rectangle();
	Rectangle(int r, int c, int h, int w);
	void draw();
};

#endif