#pragma once
#include "Shape.h"
#include "Command.h"
#include <iostream>
#include <string>

class StraightLines : public Shape
{
private:
	int x1, y1, x2, y2;

public:
	StraightLines();
	StraightLines(int, int, int, int, char *);

	static void lineTokenization(char*, int*, int*, int*, int*, char*&);
	static Shape* printLine(char*);
	virtual void printToConsole() override;
	virtual void printToFile(std::fstream&) override;
	static Shape* createLine(char*);
	static void translateLine(std::fstream&, char*, int, int);
	static void lineWithinCircle(char*, int, int, int, int*);
	static void lineWithinRectangle(char*, int, int, int, int, int*);
	
	int getX1();
	int getY1();
	int getX2();
	int getY2();

	void setX1(int);
	void setY1(int);
	void setX2(int);
	void setY2(int);

};

