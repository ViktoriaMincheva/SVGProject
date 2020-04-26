#pragma once
#include <iostream>
/*#include "Circles.h"
#include "Rectangles.h"
#include "Ellipses.h"
#include "StraightLines.h"
#include "Polylines.h"
#include "Polygons.h"*/

class Shape
{
protected:
	char* color;

public:
	static const char* RECTANGLE;
	static const char* CIRCLE;
	static const char* ELLIPSE;
	static const char* LINE;
	static const char* POLYLINE;
	static const char* POLYGON;

public: 

	virtual void printToConsole();
	static void printShape(char *, char *, int);
	char* getColor();

};

