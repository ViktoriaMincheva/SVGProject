#include "Ellipses.h"

Ellipses::Ellipses() : centerX(0), centerY(0), rx(0), ry(0)
{
}

Ellipses::Ellipses(int centerX, int centerY, unsigned int rx, unsigned int ry, char * color)
{
	this->centerX = centerX;
	this->centerY = centerY;
	this->rx = rx;
	this->ry = ry;
	this->color = new char[strlen(color) + 1];
	strcpy(this->color, color);
}

Shape* Ellipses::printEllipse(char* line, int shapeNum)
{
	char* token;
	int toPrint = 0;
	token = strtok(line, "\"");

	int val = 0;
	int centerX, centerY, rx, ry;
	char* color = new char[1];

	while (token != NULL) {

		if (toPrint % 2 == 1) {
			
			if (val == 0) {
				centerX = std::stoi(token);
				val++;
			}
			else if (val == 1) {
				centerY = std::stoi(token);
				val++;
			}
			else if (val == 2) {
				rx = std::stoi(token);
				val++;
			}
			else if (val == 3) {
				ry = std::stoi(token);
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


	return new Ellipses(centerX, centerY, rx, ry, color);
}

void Ellipses::printToConsole()
{
	std::cout << centerX << " " << centerY << " " << rx << " " << ry << " ";
	Shape::printToConsole();
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

