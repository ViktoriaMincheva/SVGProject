#include <fstream>
#include "Shape.h"
#include "Circles.h"
#include "Rectangles.h"
#include "Ellipses.h"
#include "StraightLines.h"
#include "Polylines.h"
#include "Polygons.h"

const char* Shape::RECTANGLE = "rectangle";
const char* Shape::CIRCLE = "circle";
const char* Shape::ELLIPSE = "ellipse";
const char* Shape::LINE = "line";
const char* Shape::POLYLINE = "polyline";
const char* Shape::POLYGON = "polygone";

void Shape::printToConsole()
{
	std::cout << color;
}

void Shape::printToFile(std::fstream& file)
{
	file << color;
}

void Shape::printShape(char* line, char* shapeName, int numOfShapes)
{
	int shapeNum = 0;
	for (int i = 0; i < numOfShapes; i++) {
		shapeNum++;
	}

	if (strcmp(shapeName, "<circle") == 0) {
		
		std::cout << shapeNum << ". circle ";
		Shape* circle = Circles::printCircle(line, shapeNum);
		circle->printToConsole();
		std::cout << "\n";
	}
	else if (strcmp(shapeName, "<rect") == 0) {

		std::cout << shapeNum << ". rectangle ";
		Shape* rect = Rectangles::printRectangle(line, shapeNum);
		rect->printToConsole();
		std::cout << "\n";
	}
	else if (strcmp(shapeName, "<ellipse") == 0) {

		std::cout << shapeNum << ". ellipse ";
		Shape* ellipse = Ellipses::printEllipse(line, shapeNum);
		ellipse->printToConsole();
		std::cout << "\n";
	}
	else if (strcmp(shapeName, "<line") == 0) {

		std::cout << shapeNum << ". line ";
		Shape* sLine = StraightLines::printLine(line, shapeNum);
		sLine->printToConsole();
		std::cout << "\n";
	}
	else if (strcmp(shapeName, "<polyline") == 0) {

		std::cout << shapeNum << ". polyline ";
		//Shape* polyline = Polylines::printPolyline(line, shapeNum);
		//polyline->printToConsole();
		std::cout << "\n";
	}
	else if (strcmp(shapeName, "<polygon") == 0) {

		std::cout << shapeNum << ". polygon ";
		//Shape* polygon = Polygons::printPolygon(line, shapeNum);
		//polygon->printToConsole();
		std::cout << "\n";
	}
}

char * Shape::getColor()
{
	return color;
}
