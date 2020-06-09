#include "Circles.h"
#include "Command.h"
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

void Circles::circleTokenization(char* line, int* circleX, int* circleY, int* radius, char*& circleColor)
{
	char* token;
	int toPrint = 0;
	token = strtok(line, "\"");

	int val = 0;

	while (token != NULL) {

		if (toPrint % 2 == 1) {

			if (val == 0) {
				*circleX = std::stoi(token);
				val++;
			}
			else if (val == 1) {
				*circleY = std::stoi(token);
				val++;
			}
			else if (val == 2) {
				*radius = std::stoi(token);
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
}

Shape* Circles::printCircle(char * line)
{
	int circleX = 0, circleY = 0, radius = 0;
	char* circleColor = new char[1];
	circleTokenization(line, &circleX, &circleY, &radius, circleColor);

	return  new Circles(circleX, circleY, radius, circleColor);
}

void Circles::printToConsole()
{ 
	std::cout << centerX << " " << centerY << " " << radius << " ";
	Shape::printToConsole();
}

void Circles::printToFile(std::fstream& file)
{
	file << "  <circle cx=\"" << centerX << "\" cy=\"" << centerY << "\" r=\"" << radius << "\" fill=\"";
	Shape::printToFile(file);
	file << "\" />";
}

Shape * Circles::createCircle(char * line)
{
	int val = 0;
	char* token;

	token = strtok(line, " ");
	
	int circleX = 0, circleY = 0, radius = 0;
	
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

void Circles::translateCircle(std::fstream& temp, char* lineFromFile, int verticalTr, int horizontalTr)
{

	char* tok;
	tok = strtok(lineFromFile, "\"");

	int val = 0;
	int toSkip = 0;
	int x = 0, y = 0, r = 0;
	char* circleColor = new char[1];

	while (tok != NULL) {

		if (toSkip % 2 == 1) {

			if (val == 0) {

				x = std::stoi(tok);
				x += horizontalTr;
				val++;
			}
			else if (val == 1) {
				y = std::stoi(tok);
				y += verticalTr;
				val++;
			}
			else if (val == 2) {
				r = std::stoi(tok);
				val++;
			}
			else if (val == 3) {
				circleColor = new char[strlen(tok) + 1];
				strcpy(circleColor, tok);
				val++;
			}
		}
		toSkip++;
		tok = strtok(NULL, "\"");

	}
	temp << "  <circle cx=\"" << x << "\" cy=\"" << y << "\" r=\"" << r << "\" fill=\"" << circleColor << "\" />\n";
}

void Circles::circleWithinCircle(char* lineFromFile, int circleX, int circleY, int radius, int* shapesWithin)
{
	int x = 0, y = 0, r = 0;
	char* circleColor = new char[1];
	circleTokenization(lineFromFile, &x, &y, &r, circleColor);

	int distance = sqrt(((circleX - x) * (circleX - x)) + ((circleY - y) * (circleY - y)));
	if (distance + r < radius) {
		Shape* circle = new Circles(x, y, r, circleColor);
		std::cout << "-> circle ";
		circle->printToConsole();
		shapesWithin++;
		std::cout << "\n";
	}
	else {
		return;
	}

}

void Circles::circleWithinRectangle(char* lineFromFile, int x1, int y1, int x2, int y2, int* shapesWithin)
{
	int x = 0, y = 0, r = 0;
	char* circleColor = new char[1];
	circleTokenization(lineFromFile, &x, &y, &r, circleColor);

	int counter = 0;

	bool isPointInside = true;

	for (int i = 0; i < 4; i++) {

		if (counter == 0) {
			isPointInside = Command::isInsideRectangle(x1, y1, x2, y2, x-y, y);
			counter++;
		}
		else if (counter == 1) {
			isPointInside = Command::isInsideRectangle(x1, y1, x2, y2, x, y-r);
			counter++;
		}
		else if (counter == 2) {
			isPointInside = Command::isInsideRectangle(x1, y1, x2, y2, x+r, y);
			counter++;
		}
		else if (counter == 3) {
			isPointInside = Command::isInsideRectangle(x1, y1, x2, y2, x, y+r);
			counter++;
		}

		if (isPointInside == false) {
			break;
		}
	}
	if (isPointInside == false) {
		return;
	}
	else {
		Shape* circle = new Circles(x, y, r, circleColor);
		std::cout << "-> circle ";
		circle->printToConsole();
		shapesWithin++;
		std::cout << "\n";
	}
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
