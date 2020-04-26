#pragma once
#include "Shape.h"

class Polylines : public Shape
{
private:
	int x;
	int y;

public:
	Polylines();
	Polylines(int, int);

};

