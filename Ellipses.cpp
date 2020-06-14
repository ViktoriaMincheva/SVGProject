#include "Ellipses.h"
#include <fstream>
#include <string.h>

Ellipses::Ellipses() : centerX(0), centerY(0), rx(0), ry(0)
{
	color = new char[1];
	strcpy(color, "");
}

Ellipses::Ellipses(int centerX, int centerY, int rx, int ry, char * color)
{
	this->centerX = centerX;
	this->centerY = centerY;
	this->rx = rx;
	this->ry = ry;
	this->color = new char[strlen(color) + 1];
	strcpy(this->color, color);
}

void Ellipses::ellipseTokenization(char* line, int* centerX, int* centerY, int* rx, int* ry, char*& color)
{
	char* token;
	int toPrint = 0;
	token = strtok(line, "\"");

	int val = 0;
	while (token != NULL) {

		if (toPrint % 2 == 1) {

			if (val == 0) {
				*centerX = std::stoi(token);
				val++;
			}
			else if (val == 1) {
				*centerY = std::stoi(token);
				val++;
			}
			else if (val == 2) {
				*rx = std::stoi(token);
				val++;
			}
			else if (val == 3) {
				*ry = std::stoi(token);
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

Shape* Ellipses::printEllipse(char* line)
{
	int centerX = 0, centerY = 0, rx = 0, ry = 0;
	char* color = new char[1];
	ellipseTokenization(line, &centerX, &centerY, &rx, &ry, color);

	return new Ellipses(centerX, centerY, rx, ry, color);
}

void Ellipses::printToConsole()
{
	std::cout << centerX << " " << centerY << " " << rx << " " << ry << " ";
	Shape::printToConsole();
}

void Ellipses::printToFile(std::fstream& file)
{
	file << "  <ellipse cx=\"" << centerX << "\" cy=\"" << centerY << "\" rx=\"" << rx << "\" ry=\"" << ry << "\" fill=\"";
	Shape::printToFile(file);
	file << "\" />";
}

Shape* Ellipses::createEllipse(char* line)
{
	int val = 0;
	char* token;

	token = strtok(line, " ");
	int cX = 0, cY = 0, rX = 0, rY = 0;
	char* ellipseColor = new char[1];

	while (token != NULL) {

		if (val < 2) {
			val++;
		}
		else if (val == 2) {
			cX = std::stoi(token);
			val++;
		}
		else if (val == 3) {
			cY = std::stoi(token);
			val++;
		}
		else if (val == 4) {
			rX = std::stoi(token);
			val++;
		}
		else if (val == 5) {
			rY = std::stoi(token);
			val++;
		}
		else if (val == 6) {
			ellipseColor = new char[strlen(token) + 1];
			strcpy(ellipseColor, token);
			val++;
		}

		token = strtok(NULL, " ");
	}

	return new Ellipses(cX, cY, rX, rY, ellipseColor);
}

void Ellipses::translateEllipse(std::fstream& temp, char* lineFromFile, int verticalTr, int horizontalTr)
{
	char* tok;
	tok = strtok(lineFromFile, "\"");

	int val = 0;
	int toSkip = 0;
	int centerX = 0, centerY = 0, rx = 0, ry = 0;
	char* color = new char[1];

	while (tok != NULL) {

		if (toSkip % 2 == 1) {

			if (val == 0) {
				centerX = std::stoi(tok);
				centerX += horizontalTr;
				val++;
			}
			else if (val == 1) {
				centerY = std::stoi(tok);
				centerY += verticalTr;
				val++;
			}
			else if (val == 2) {
				rx = std::stoi(tok);
				rx += horizontalTr;
				val++;
			}
			else if (val == 3) {
				ry = std::stoi(tok);
				ry += verticalTr;
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
	temp << "  <ellipse cx=\"" << centerX << "\" cy=\"" << centerY << "\" rx=\"" << rx << "\" ry=\"" << ry << "\" fill=\"" << color << "\" />\n";
}

void Ellipses::ellipseWithinCircle(char* lineFromFile, int circleX, int circleY, int radius, int* shapesWithin)
{
	
	int centerX = 0, centerY = 0, rx = 0, ry = 0;
	char* color = new char[1];
	ellipseTokenization(lineFromFile, &centerX, &centerY, &rx, &ry, color);
	
	int counter = 0;
	int newX = 0, newY = 0;
	bool isPointInside = true;

	for (int i = 0; i < 2; i++) {

		if (counter == 0) {
			isPointInside = Command::isInsideCircle(circleX, circleY, radius, centerX - rx, centerY - ry);
			counter++;
		}
		else if (counter == 1) {
			isPointInside = Command::isInsideCircle(circleX, circleY, radius, centerX + rx, centerY + ry);
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
		Shape* ellipse = new Ellipses(centerX, centerY, rx, ry, color);
		std::cout << "-> ellipse ";
		ellipse->printToConsole();
		shapesWithin++;
		std::cout << "\n";
	}
}

void Ellipses::ellipseWithinRectangle(char* lineFromFile, int x1, int y1, int x2, int y2, int* shapesWithin)
{
	int centerX = 0, centerY = 0, rx = 0, ry = 0;
	char* color = new char[1];
	ellipseTokenization(lineFromFile, &centerX, &centerY, &rx, &ry, color);

	int counter = 0;
	int newX = 0, newY = 0;
	bool isPointInside = true;

	for (int i = 0; i < 2; i++) {

		if (counter == 0) {
			isPointInside = Command::isInsideRectangle(x1, y1, x2, y2, centerX - rx, centerY - ry);
			counter++;
		}
		else if (counter == 1) {
			isPointInside = Command::isInsideRectangle(x1, y1, x2, y2, centerX + rx, centerY + ry);
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
		Shape* ellipse = new Ellipses(centerX, centerY, rx, ry, color);
		std::cout << "-> ellipse ";
		ellipse->printToConsole();
		shapesWithin++;
		std::cout << "\n";
	}
}

int Ellipses::getX()
{
	return centerX;
}

int Ellipses::getY()
{
	return centerY;
}

int Ellipses::getRX()
{
	return rx;
}

int Ellipses::getRY()
{
	return ry;
}

void Ellipses::setX(int newCenterX)
{
	centerX = newCenterX;
}

void Ellipses::setY(int newCenterY)
{
	centerX = newCenterY;
}

void Ellipses::setRX(int newRX)
{
	rx = newRX;
}

void Ellipses::setRY(int newRX)
{
	rx = newRX;
}

