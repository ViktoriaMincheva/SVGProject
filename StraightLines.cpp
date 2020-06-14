#include "StraightLines.h"
#include <fstream>
#include <string.h>

StraightLines::StraightLines() : x1(0), y1(0), x2(0), y2(0)
{
	color = new char[1];
	strcpy(color, "");
}

StraightLines::StraightLines(int x1, int y1, int x2, int y2, char * color)
{
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
	this->color = new char[strlen(color) + 1];
	strcpy(this->color, color);
}

void StraightLines::lineTokenization(char* line, int* x1, int* y1, int* x2, int* y2, char*& color)
{
	char* token;
	int toPrint = 0;
	token = strtok(line, "\"");

	int val = 0;
	while (token != NULL) {

		if (toPrint % 2 == 1) {

			if (val == 0) {
				*x1 = std::stoi(token);
				val++;
			}
			else if (val == 1) {
				*y1 = std::stoi(token);
				val++;
			}
			else if (val == 2) {
				*x2 = std::stoi(token);
				val++;
			}
			else if (val == 3) {
				*y2 = std::stoi(token);
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

Shape* StraightLines::printLine(char* line)
{
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	char* color = new char[1];
	lineTokenization(line, &x1, &y1, &x2, &y2, color);

	return new StraightLines(x1, y1, x2, y2, color);
}

void StraightLines::printToConsole()
{
	std::cout << x1 << " " << y1 << " " << x2 << " " << y2 << " ";
	Shape::printToConsole();
}

void StraightLines::printToFile(std::fstream& file)
{
	file << "  <line x1=\"" << x1 << "\" y1=\"" << y1 << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\" fill=\"";
	Shape::printToFile(file);
	file << "\" />";
}

Shape* StraightLines::createLine(char* line)
{
	int val = 0;
	char* token;

	token = strtok(line, " ");
	int newX1 = 0, newY1 = 0, newX2 = 0, newY2 = 0;
	char* lineColor = new char[1];
	while (token != NULL) {

		if (val < 2) {
			val++;
		}
		else if (val == 2) {
			newX1 = std::stoi(token);
			val++;
		}
		else if (val == 3) {
			newY1 = std::stoi(token);
			val++;
		}
		else if (val == 4) {
			newX2 = std::stoi(token);
			val++;
		}
		else if (val == 5) {
			newY2 = std::stoi(token);
			val++;
		}
		else if (val == 6) {
			lineColor = new char[strlen(token) + 1];
			strcpy(lineColor, token);
			val++;
		}

		token = strtok(NULL, " ");
	}

	return new StraightLines(newX1, newY1, newX2, newY2, lineColor);
}

void StraightLines::translateLine(std::fstream& temp, char* lineFromFile, int verticalTr, int horizontalTr)
{
	char* tok;
	tok = strtok(lineFromFile, "\"");

	int val = 0;
	int toSkip = 0;
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	char* color = new char[1];

	while (tok != NULL) {

		if (toSkip % 2 == 1) {

			if (val == 0) {
				x1 = std::stoi(tok);
				x1 += horizontalTr;
				val++;
			}
			else if (val == 1) {
				y1 = std::stoi(tok);
				y1 += verticalTr;
				val++;
			}
			else if (val == 2) {
				x2 = std::stoi(tok);
				x2 += horizontalTr;
				val++;
			}
			else if (val == 3) {
				y2 = std::stoi(tok);
				y2 += verticalTr;
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
	temp << "  <line x1=\"" << x1 << "\" y1=\"" << y1 << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\" fill=\"" << color << "\" />\n";
}

void StraightLines::lineWithinCircle(char* lineFromFile, int circleX, int circleY, int radius, int* shapesWithin)
{
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	char* color = new char[1];
	lineTokenization(lineFromFile, &x1, &y1, &x2, &y2, color);
	
	int counter = 0;
	bool isPointInside = true;

	for (int i = 0; i < 2; i++) {

		if (counter == 0) {
			isPointInside = Command::isInsideCircle(circleX, circleY, radius, x1, y1);
			counter++;
		}
		else if (counter == 1) {
			isPointInside = Command::isInsideCircle(circleX, circleY, radius, x2, y2);
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
		Shape* line = new StraightLines(x1, y1, x2, y2, color);
		std::cout << "-> line ";
		line->printToConsole();
		(*shapesWithin)++;
		std::cout << "\n";
	}
}

void StraightLines::lineWithinRectangle(char* lineFromFile, int x1, int y1, int x2, int y2, int* shapesWithin)
{
	int x1line = 0, y1line = 0, x2line = 0, y2line = 0;
	char* color = new char[1];
	lineTokenization(lineFromFile, &x1line, &y1line, &x2line, &y2line, color);

	int counter = 0;
	bool isPointInside = true;

	for (int i = 0; i < 2; i++) {

		if (counter == 0) {
			isPointInside = Command::isInsideRectangle(x1, y1, x2, y2, x1line, y1line);
			counter++;
		}
		else if (counter == 1) {
			isPointInside = Command::isInsideRectangle(x1, y1, x2, y2, x2line, y2line);
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
		Shape* line = new StraightLines(x1line, y1line, x2line, y2line, color);
		std::cout << "-> line ";
		line->printToConsole();
		shapesWithin++;
		std::cout << "\n";
	}
}

int StraightLines::getX1()
{
	return x1;
}

int StraightLines::getY1()
{
	return y1;
}

int StraightLines::getX2()
{
	return x2;
}

int StraightLines::getY2()
{
	return y2;
}
void StraightLines::setX1(int newX1) {
	x1 = newX1;
}

void StraightLines::setY1(int newY1) {
	y1 = newY1;
}

void StraightLines::setX2(int newX2) {
	x2 = newX2;
}

void StraightLines::setY2(int newY2) {
	y2 = newY2;
}
