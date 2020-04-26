#include "Rectangles.h"

Rectangles::Rectangles() : x(0), y(0), width (0), height(0)
{
}

Rectangles::Rectangles(int x, int y, int width, int height, char* color)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->color = new char[strlen(color) + 1];
	strcpy(this->color, color);
}

Shape* Rectangles::printRectangle(char* line, int shapeNum)
{
	char* token;
	int toPrint = 0;
	token = strtok(line, "\"");

	int val = 0;
	int x, y, width, height = 0;
	char* color = new char[1];


	while (token != NULL) {
		
		if (toPrint % 2 == 1) {
			
			if (val == 0) {
				x = std::stoi(token);
				val++;
			}
			else if (val == 1) {
				y = std::stoi(token);
				val++;
			}
			else if (val == 2) {
				width = std::stoi(token);
				val++;
			}
			else if (val == 3) {
				height = std::stoi(token);
				val++;
			}
			else if (val == 4) {
				color = new char[strlen(token) + 1];
				strcpy(color, token);
				val++;
			}

		}

		toPrint++;
		token = strtok(NULL, "\"");
	}

	return new Rectangles(x, y, width, height, color);
}

void Rectangles::printToConsole()
{
	std::cout << x << " " << y << " " << width << " " << height << " ";
	Shape::printToConsole();
}

int Rectangles::getX()
{
	return x;
}

int Rectangles::getY()
{
	return y;
}

int Rectangles::getWidth()
{
	return width;
}

int Rectangles::getHeight()
{
	return height;
}

void Rectangles::setX(int newX)
{
	x = newX;
}

void Rectangles::setY(int newY)
{
	y = newY;
}

void Rectangles::setWidth(int newWidth)
{
	width = newWidth;
}

void Rectangles::setHeight(int newHeight)
{
	height = newHeight;
}
