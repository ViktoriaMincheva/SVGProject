#pragma once
#include "Shape.h"
#include <iostream>
#include <string>

class Circles : public Shape
{
private:
	int centerX;
	int centerY;
	int radius;

public:
	Circles();
	Circles(int, int, int, char *);

	static void circleTokenization(char *, int*, int*, int*, char*&);
	static Shape* printCircle(char *);
	virtual void printToConsole() override;
	virtual void printToFile(std::fstream&) override;
	static Shape* createCircle(char *);
	static void translateCircle(std::fstream&, char *, int, int);
	static void circleWithinCircle(char *, int, int, int, int*);
	static void circleWithinRectangle(char*, int, int, int, int, int*);

	int getX();
	int getY();
	int getRadius();
	void setX(int);
	void setY(int); 
	void setRadius(int);


};

