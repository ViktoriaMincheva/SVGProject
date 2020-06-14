#pragma once
#include <iostream>

class Shape
{
protected:
	char* color;

public:
	static const char* RECTANGLE;
	static const char* CIRCLE;
	static const char* ELLIPSE;
	static const char* LINE;
	static const char* POLYLINE;
	static const char* POLYGON;

public: 
	Shape();
	Shape(const char*);
	Shape(const Shape&);
	Shape operator=(const Shape&);
	~Shape();

	virtual void printToConsole();
	virtual void printToFile(std::fstream& file);
	static void printShape(char *, char *, int);
	char* getColor();
	void setColor(const char*);

};

