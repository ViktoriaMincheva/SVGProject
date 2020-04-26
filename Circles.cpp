#include "Circles.h"
#include <fstream>
#include <string.h>

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
	char* circleColor = new char[1];
	while (token != NULL) {

		if (toPrint % 2 == 1) {
			
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
		toPrint++;
		token = strtok(NULL, "\"");
	}

	return  new Circles(circleX, circleY, radius, circleColor);
}

void Circles::printToConsole()
{ 
	std::cout << centerX << " " << centerY << " " << radius << " ";
	Shape::printToConsole();
}

void Circles::printToFile(std::fstream& file)
{ //<circle cx="5" cy="5" r="10" fill="blue" />
	file << "  <circle cx=\"" << centerX << "\" cy=\"" << centerY << "\" r=\"" << radius << "\" fill=\"" << color << "\" />";
}

Shape * Circles::createCircle(char * line)
{
	int val = 0;
	char* token;
	
	token = strtok(line, " ");
	
	int circleX, circleY, radius;
	
	//char* circleColor = new char[4];
	//strcpy(circleColor, "red");
	char* circleColor = new char[1];

	while (token != NULL) {

		if (val < 2) {
			val++;
		} 
		else if (val == 2) {
			circleX = std::stoi(token);
			val++;
		}
		else if (val == 3) {
			circleY = std::stoi(token);
			val++;
		}
		else if (val == 4) {
			radius = std::stoi(token);
			val++;
		}
		else if (val == 5) {
			circleColor = new char[strlen(token) + 1];
			strcpy(circleColor, token);
			val++;
		}
	
		token = strtok(NULL, " ");
	}
	
	return new Circles(circleX, circleY, radius, circleColor);
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
