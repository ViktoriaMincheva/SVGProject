#include "Rectangles.h"
#include <fstream>
#include <string.h>

Rectangles::Rectangles() : x(0), y(0), width (0), height(0)
{
	color = new char[1];
	strcpy(color, "");
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

void Rectangles::rectangleTokenization(char* line, int* x, int* y, int* width, int* height, char*& color)
{
	char* token;
	int toPrint = 0;
	token = strtok(line, "\"");

	int val = 0;
	while (token != NULL) {

		if (toPrint % 2 == 1) {

			if (val == 0) {
				*x = std::stoi(token);
				val++;
			}
			else if (val == 1) {
				*y = std::stoi(token);
				val++;
			}
			else if (val == 2) {
				*width = std::stoi(token);
				val++;
			}
			else if (val == 3) {
				*height = std::stoi(token);
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
}

Shape* Rectangles::printRectangle(char* line)
{
	int x = 0, y = 0, width = 0, height = 0;
	char* color = new char[1];
	rectangleTokenization(line, &x, &y, &width, &height, color);

	return new Rectangles(x, y, width, height, color);
}

void Rectangles::printToConsole()
{
	std::cout << x << " " << y << " " << width << " " << height << " ";
	Shape::printToConsole();
}

void Rectangles::printToFile(std::fstream& file)
{
	file << "  <rect x=\"" << x << "\" y=\"" << y << "\" width=\"" << width << "\" height=\"" << height << "\" fill=\"";
	Shape::printToFile(file);
	file << "\" />";
}

Shape* Rectangles::createRectangle(char* line)
{
	int val = 0;
	char* token;
	 
	token = strtok(line, " ");
	int newX = 0, newY = 0, newWidth = 0, newHeight = 0;
	char* rectColor = new char[1];

	while (token != NULL) {

		if (val < 2) {
			val++;
		}
		else if (val == 2) {
			newX = std::stoi(token);
			val++;
		}
		else if (val == 3) {
			newY = std::stoi(token);
			val++;
		}
		else if (val == 4) {
			newWidth = std::stoi(token);
			val++;
		}
		else if (val == 5) {
			newHeight = std::stoi(token);
			val++;
		}
		else if (val == 6) {
			rectColor = new char[strlen(token) + 1];
			strcpy(rectColor, token);
			val++;
		}

		token = strtok(NULL, " ");
	}

	return new Rectangles(newX, newY, newWidth, newHeight, rectColor);
}

void Rectangles::translateRectangle(std::fstream& temp, char* lineFromFile, int verticalTr, int horizontalTr)
{
	char* tok;
	tok = strtok(lineFromFile, "\"");

	int val = 0;
	int toSkip = 0;
	int x = 0, y = 0, width = 0, height = 0;
	char* color = new char[1];

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
				width = std::stoi(tok);
				val++;
			}
			else if (val == 3) {
				height = std::stoi(tok);
				val++;
			}
			else if (val == 4) {
				color = new char[strlen(tok) + 1];
				strcpy(color, tok);
				val++;
			}

		}

		toSkip++;
		tok = strtok(NULL, "\"");
	}

	temp << "  <rect x=\"" << x << "\" y=\"" << y << "\" width=\"" << width << "\" height=\"" << height << "\" fill=\"" << color << "\" />\n";

}

void Rectangles::rectangleWithinCircle(char* lineFromFile, int circleX, int circleY, int radius, int* shapesWithin)
{
	int x = 0, y = 0, width = 0, height = 0;
	char* color = new char[1];
	rectangleTokenization(lineFromFile, &x, &y, &width, &height, color);

	int counter = 0;

	bool isPointInside = true;

	for (int i = 0; i < 4; i++) {

		if (counter == 0) {
			isPointInside = Command::isInsideCircle(circleX, circleY, radius, x, y);
			counter++;
		}
		else if (counter == 1) {
			isPointInside = Command::isInsideCircle(circleX, circleY, radius, x + width, y);
			counter++;
		}
		else if (counter == 2) {
			isPointInside = Command::isInsideCircle(circleX, circleY, radius, x, y - height);
			counter++;
		}
		else if (counter == 3) {
			isPointInside = Command::isInsideCircle(circleX, circleY, radius, x + width, y - height);
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
		Shape* rectangle = new Rectangles(x, y, width, height, color);
		std::cout << "-> rectangle ";
		rectangle->printToConsole();
		shapesWithin++;
		std::cout << "\n";
	}
}

void Rectangles::rectangleWithinRectangle(char* lineFromFile, int x1, int y1, int x2, int y2, int* shapesWithin)
{
	int x = 0, y = 0, width = 0, height = 0;
	char* color = new char[1];
	rectangleTokenization(lineFromFile, &x, &y, &width, &height, color);

	int counter = 0;

	bool isPointInside = true;

	for (int i = 0; i < 4; i++) {

		if (counter == 0) {
			isPointInside = Command::isInsideRectangle(x1, y1, x2, y2, x, y);
			counter++;
		}
		else if (counter == 1) {
			isPointInside = Command::isInsideRectangle(x1, y1, x2, y2, x - width, y);
			counter++;
		}
		else if (counter == 2) {
			isPointInside = Command::isInsideRectangle(x1, y1, x2, y2, x, y - height);
			counter++;
		}
		else if (counter == 3) {
			isPointInside = Command::isInsideRectangle(x1, y1, x2, y2, x + width, y - height);
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
		Shape* rectangle = new Rectangles(x, y, width, height, color);
		std::cout << "-> rectangle ";
		rectangle->printToConsole();
		shapesWithin++;
		std::cout << "\n";
	}
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
