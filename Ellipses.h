#pragma once
#include "Shape.h"
#include <iostream>
#include <string>

class Ellipses : public Shape
{
private:
	int centerX; //centerX
	int centerY;
	unsigned int rx; //radiusX
	unsigned int ry; // ������ ����, �� �� ���� �� �� �����������

public:
	Ellipses();
	Ellipses(int, int, unsigned int, unsigned int, char *);

	static Shape* printEllipse(char*, int);
	virtual void printToConsole() override;
	int getX();
	int getY();
	int getRX();
	int getRY();
	void setX(int);
	void setY(int);
	void setRX(int);
	void setRY(int);
};

