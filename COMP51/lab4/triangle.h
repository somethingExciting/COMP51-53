/************************************************************
 * File: triangle.h
 * Description: Header file for the Triangle class, which
 *              is derived from the Shape class and is used
 *              to display triangles of stars on the screen.
 ***********************************************************/

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.h"

class Triangle : public Shape
{
protected:
	// inherits location of the rectangle from parent
	// size of the isosceles triangle in stars.
	int width;
public:
	Triangle();
	Triangle(int r, int c, int w);
	void draw();
};

#endif