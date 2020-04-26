#include "StraightLines.h"

StraightLines::StraightLines() : x1(0), y1(0), x2(0), y2(0)
{
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

Shape* StraightLines::printLine(char* line, int shapeNum)
{
	char* token;
	int toPrint = 0;
	token = strtok(line, "\"");

	int val = 0;
	int x1, y1, x2, y2;
	char* color = new char[1];
	while (token != NULL) {

		if (toPrint % 2 == 1) {
			
			if (val == 0) {
				x1 = std::stoi(token);
				val++;
			}
			else if (val == 1) {
				y1 = std::stoi(token);
				val++;
			}
			else if (val == 2) {
				x2 = std::stoi(token);
				val++;
			}
			else if (val == 3) {
				y2 = std::stoi(token);
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

	return new StraightLines(x1, y1, x2, y2, color);
}

void StraightLines::printToConsole()
{
	std::cout << x1 << " " << y1 << " " << x2 << " " << y2 << " ";
	Shape::printToConsole();
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
