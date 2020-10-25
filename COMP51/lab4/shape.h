/***********************************************************
 * File: shape.h
 * Description: Header file for the Shape class, from which
 *              the Rectangle and Triangle will be derived.
 **********************************************************/

#ifndef SHAPE_H
#define SHAPE_H

class Shape
{
protected:
	// location of the top left corner: starting at 0,0
	int row;
	int col;
public:
	Shape();
	Shape(int r, int c);
	virtual void draw() = 0;
};
#endif