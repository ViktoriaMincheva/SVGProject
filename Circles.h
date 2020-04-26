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

	static Shape* printCircle(char *, int);
	virtual void printToConsole() override;
	virtual void printToFile(std::fstream&) override;
	static Shape * createCircle(char *);
	int getX();
	int getY();
	int getRadius();
	void setX(int);
	void setY(int); 
	void setRadius(int);


};

