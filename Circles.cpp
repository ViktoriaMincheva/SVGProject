#include "Circles.h"

Circles::Circles() : centerX(0), centerY(0), radius(0)
{
}

Circles::Circles(int centerX, int centerY, int radius, char * color)
{
	this->centerX = centerX;
	this->centerY = centerY;
	this->radius = radius;
	this->color = new char[strlen(color) + 1];
	strcpy(this->color, color);
}

Shape* Circles::printCircle(char * line, int shapeNum)
{
	char* token;
	int toPrint = 0;
	token = strtok(line, "\"");

	int val = 0;
	int circleX, circleY, radius;
	char* circleColor;
	while (token != NULL) {

		if (toPrint % 2 == 1) {
			toPrint++;
			if (val == 0) {
				circleX = std::stoi(token);
				val++;
			}
			else if (val == 1) {
				circleY = std::stoi(token);
				val++;
			}
			else if (val == 2) {
				radius = std::stoi(token);
				val++;
			}
			else if (val == 3) {
				circleColor = new char[strlen(token) + 1];
				strcpy(circleColor, token);
				val++;
			}
		}

		token = strtok(NULL, "\"");
	}

	return  new Circles(circleX, circleY, radius, circleColor);
}

void Circles::printToConsole()
{ 
	std::cout << centerX << " " << centerY << " " << radius;
	Shape::printToConsole();
}

int Circles::getX()
{
	return centerX;
}

int Circles::getY()
{
	return centerY;
}

int Circles::getRadius()
{
	return radius;
}

void Circles::setY(int newY)
{
	centerY = newY;
}

void Circles::setRadius(int newRadius)
{
	radius = newRadius;
}

void Circles::setX(int newX)
{
	centerX = newX;
}
