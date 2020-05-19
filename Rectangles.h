#pragma once
#include "Shape.h"
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
	
	static Shape* printRectangle(char*, int);
	virtual void printToConsole() override;
	virtual void printToFile(std::fstream&) override;
	static Shape* createRectangle(char*);
	int getX();
	int getY();
	int getWidth();
	int getHeight();

	void setX(int);
	void setY(int);
	void setWidth(int);
	void setHeight(int);

};

