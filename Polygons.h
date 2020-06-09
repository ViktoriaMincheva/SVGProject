#pragma once
#include "Shape.h"
#include "Point.h"
#include "Command.h"

class Polygons : public Shape
{
private:
	Point** points;
	int capacity;
	int curr;

public:
	Polygons();
	Polygons(int);
	Polygons(Point**, int);


	void add(Point*);
	static Shape* createPolygon(char*);
	static Shape* printPolygon(char*);
	virtual void printToConsole() override;
	virtual void printToFile(std::fstream&) override;
	static void translatePolygon(std::fstream&, char*, int, int);
	static void polygonWithinCircle(char*, int, int, int, int*);
	static void polygonWithinRectangle(char*, int, int, int, int, int*);

	void setColor(char*);
};

