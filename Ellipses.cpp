#include "Ellipses.h"
#include <fstream>
#include <string.h>

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
	int centerX = 0, centerY = 0, rx = 0, ry = 0;
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

