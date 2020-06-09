#pragma once
#include "Shape.h"
#include "Command.h"
#include <iostream>
#include <string>

class Ellipses : public Shape
{
private:
	int centerX;
	int centerY;
	int rx; 
	int ry; 

public:
	Ellipses();
	Ellipses(int, int, int, int, char *);

	static void ellipseTokenization(char*, int*, int*, int*, int*, char*&);
	static Shape* printEllipse(char*);
	virtual void printToConsole() override;
	virtual void printToFile(std::fstream&) override;
	static Shape* createEllipse(char*);
	static void translateEllipse(std::fstream&, char*, int, int);
	static void ellipseWithinCircle(char*, int, int, int, int*);
	static void ellipseWithinRectangle(char*, int, int, int, int, int*);

	int getX();
	int getY();
	int getRX();
	int getRY();
	void setX(int);
	void setY(int);
	void setRX(int);
	void setRY(int);
};

