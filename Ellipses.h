#pragma once
#include "Shape.h"
#include <iostream>
#include <string>

class Ellipses : public Shape
{
private:
	int centerX; //centerX
	int centerY;
	int rx; 
	int ry; 

public:
	Ellipses();
	Ellipses(int, int, int, int, char *);

	static Shape* printEllipse(char*, int);
	virtual void printToConsole() override;
	virtual void printToFile(std::fstream&) override;
	static Shape* createEllipse(char*);

	int getX();
	int getY();
	int getRX();
	int getRY();
	void setX(int);
	void setY(int);
	void setRX(int);
	void setRY(int);
};

