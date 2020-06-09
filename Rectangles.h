#pragma once
#include "Shape.h"
#include "Command.h"
#include <iostream>
#include <string>

class Rectangles : public Shape
{
private:
	int x;
	int y;
	int width;
	int height;

public:
	Rectangles();
	Rectangles(int, int, int, int, char *);
	
	static void rectangleTokenization(char*, int*, int*, int*, int*, char*&);
	static Shape* printRectangle(char*);
	virtual void printToConsole() override;
	virtual void printToFile(std::fstream&) override;
	static Shape* createRectangle(char*);
	static void translateRectangle(std::fstream&, char*, int, int);
	static void rectangleWithinCircle(char*, int, int, int, int*);
	static void rectangleWithinRectangle(char*, int, int, int, int, int*);

	int getX();
	int getY();
	int getWidth();
	int getHeight();

	void setX(int);
	void setY(int);
	void setWidth(int);
	void setHeight(int);

};

