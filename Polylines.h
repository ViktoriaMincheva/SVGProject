#pragma once
#include "Shape.h"
#include "Point.h"
#include "Command.h"

class Polylines : public Shape
{
private:
	Point** points;
	int capacity;
	int curr;

public:
	Polylines();
	Polylines(int);
	Polylines(Point**, int);


	void add(Point*);
	static Shape* createPolyline(char*);
	static Shape* printPolyline(char*);
	virtual void printToConsole() override;
	virtual void printToFile(std::fstream&) override;
	static void translatePolyline(std::fstream&, char*, int, int);
	static void polylineWithinCircle(char*, int, int, int, int*);
	static void polylineWithinRectnagle(char*, int, int, int, int, int*);

	void setColor(char *);

};

