#pragma once
#include "Shape.h"
#include <iostream>
#include <string>

class StraightLines : public Shape
{
private:
	int x1, y1, x2, y2;

public:
	StraightLines();
	StraightLines(int, int, int, int, char *);

	static Shape* printLine(char*, int);
	virtual void printToConsole() override;
	
	int getX1();
	int getY1();
	int getX2();
	int getY2();

	void setX1(int);
	void setY1(int);
	void setX2(int);
	void setY2(int);

};

