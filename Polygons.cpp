#include "Polygons.h"
#include <string>
#include <fstream>

Polygons::Polygons()
{
	capacity = 1;
	curr = 0;
	points = new Point * [capacity];
}

Polygons::Polygons(int cap)
{
	capacity = cap;
	curr = 0;
	points = new Point * [capacity];
}

Polygons::Polygons(Point** ps, int cap)
{
	capacity = cap;
	curr = 0;
	points = new Point * [capacity];

	for (; curr < capacity; curr++) {
		points[curr] = new Point(ps[curr]->getX(), ps[curr]->getY());
	}
}

void Polygons::add(Point* point)
{
	points[curr] = new Point(point->getX(), point->getY());
	curr++;
}

Shape* Polygons::createPolygon(char* line)
{
	int j = strlen(line);
	int lenght = j - 15;
	char* lineCopy = new char[lenght];

	int k = 0;
	for (int i = 15; i < j; i++) {
		lineCopy[k] = line[i];
		k++;
	}
	lineCopy[lenght] = '\0';

	int numOfSpaces = 0;

	for (size_t i = 0; i < strlen(lineCopy); i++) {
		if (lineCopy[i] == ' ') {
			numOfSpaces++;
		}
	}

	if (numOfSpaces % 2 == 1 || numOfSpaces < 6) {
		std::cerr << "Invalid number of points! Polygon needs at least 3 points to be a polygon! " << std::endl;
		return nullptr;
	}

	char* token;
	token = strtok(lineCopy, " ");

	int val = 0, x, y, spaces = 0;
	char* color = new char[1];

	Polygons* polygon = new Polygons(numOfSpaces / 2);


	while (token != NULL) {

		if (spaces < numOfSpaces) {
			if (val % 2 == 0) { // chetno
				x = std::stoi(token);
				spaces++;
			}
			else if (val % 2 == 1) {
				y = std::stoi(token);
				spaces++;
				polygon->add(new Point(x, y));
			}
		}
		else {
			color = new char[strlen(token)];
			strcpy(color, token);
			break;
		}

		val++;
		token = strtok(NULL, " ");
	}
	polygon->setColor(color);

	return polygon;
}

Shape* Polygons::printPolygon(char* line)
{
	int numOfCommas = 0;

	for (size_t i = 0; i < strlen(line); i++) {
		if (line[i] == ',') {
			numOfCommas++;
		}
	}

	char delimiter = '\"';
	int size1 = 0;
	char** s1 = Command::strSplit(line, delimiter, &size1);
	char* color = new char[1];
	int x = 0, y = 0;


	Polygons* polygon = new Polygons(numOfCommas);

	for (int i = 0; i < size1; i++) {
		if (i == 1) {
			
			int size2 = 0;
			char** s2 = Command::strSplit(s1[i], ' ', &size2);
			for (int j = 0; j < size2; j++) {
				int size3 = 0;
				char** s3 = Command::strSplit(s2[j], ',', &size3);

				x = std::stoi(s3[0]);
				y = std::stoi(s3[1]);
				polygon->add(new Point(x, y));
				
			}
		}
		if (i == 3) {
			
			color = new char[strlen(s1[i])];
			strcpy(color, s1[i]);
		}
	}
	polygon->setColor(color);

	return polygon;
}

void Polygons::printToConsole()
{
	for (int i = 0; i < capacity; i++) {
		std::cout << points[i]->getX() << "," << points[i]->getY() << " ";
	}
	Shape::printToConsole();
}

void Polygons::printToFile(std::fstream& file)
{
	file << "  <polygon points=\"";
	for (int i = 0; i < capacity; i++) {
		file << points[i]->getX() << "," << points[i]->getY();
		if (i == capacity - 1) {
			file << "\"";
		}
		else {
			file << " ";
		}
	}
	file << " fill=\"";
	Shape::printToFile(file);
	file << "\" />";
}

void Polygons::translatePolygon(std::fstream& temp, char* lineFromFile, int verticalTr, int horizontalTr)
{
	int numOfCommas = 0;

	for (size_t i = 0; i < strlen(lineFromFile); i++) {
		if (lineFromFile[i] == ',') {
			numOfCommas++;
		}
	}

	char delimiter = '\"';
	int size1 = 0;
	char** s1 = Command::strSplit(lineFromFile, delimiter, &size1);
	char* color = new char[1];
	int x = 0, y = 0;


	Polygons* polygon = new Polygons(numOfCommas);

	for (int i = 0; i < size1; i++) {
		if (i == 1) {

			int size2 = 0;
			char** s2 = Command::strSplit(s1[i], ' ', &size2);
			for (int j = 0; j < size2; j++) {
				int size3 = 0;
				char** s3 = Command::strSplit(s2[j], ',', &size3);

				x = std::stoi(s3[0]);
				x += horizontalTr;
				y = std::stoi(s3[1]);
				y += verticalTr;
				polygon->add(new Point(x, y));

			}
		}
		if (i == 3) {
			color = new char[strlen(s1[i])];
			strcpy(color, s1[i]);
		}
	}
	polygon->setColor(color);

	polygon->printToFile(temp);
	temp << "\n";
}

void Polygons::polygonWithinCircle(char* lineFromFile, int circleX, int circleY, int radius, int* shapesWithin)
{
	int numOfCommas = 0;

	for (size_t i = 0; i < strlen(lineFromFile); i++) {
		if (lineFromFile[i] == ',') {
			numOfCommas++;
		}
	}

	char delimiter = '\"';
	int size1 = 0;
	char** s1 = Command::strSplit(lineFromFile, delimiter, &size1);
	char* color = new char[1];
	int x = 0, y = 0;


	Polygons* polygon = new Polygons(numOfCommas);
	bool isPointInside = true;

	for (int i = 0; i < size1; i++) {
		if (i == 1) {

			int size2 = 0;
			char** s2 = Command::strSplit(s1[i], ' ', &size2);
			for (int j = 0; j < size2; j++) {
				int size3 = 0;
				char** s3 = Command::strSplit(s2[j], ',', &size3);

				x = std::stoi(s3[0]);
				y = std::stoi(s3[1]);

				isPointInside = Command::isInsideCircle(circleX, circleY, radius, x, y);

				if (isPointInside == false) {
					return;
				}

				polygon->add(new Point(x, y));

			}
		}
		if (i == 3) {

			color = new char[strlen(s1[i])];
			strcpy(color, s1[i]);
		}
	}
	polygon->setColor(color);
	std::cout << "-> polygon ";
	polygon->printToConsole();
	(*shapesWithin)++;
	std::cout << "\n";
}

void Polygons::polygonWithinRectangle(char* lineFromFile, int x1, int y1, int x2, int y2, int* shapesWithin)
{
	int numOfCommas = 0;

	for (size_t i = 0; i < strlen(lineFromFile); i++) {
		if (lineFromFile[i] == ',') {
			numOfCommas++;
		}
	}

	char delimiter = '\"';
	int size1 = 0;
	char** s1 = Command::strSplit(lineFromFile, delimiter, &size1);
	char* color = new char[1];
	int x = 0, y = 0;


	Polygons* polygon = new Polygons(numOfCommas);
	bool isPointInside = true;

	for (int i = 0; i < size1; i++) {
		if (i == 1) {

			int size2 = 0;
			char** s2 = Command::strSplit(s1[i], ' ', &size2);
			for (int j = 0; j < size2; j++) {
				int size3 = 0;
				char** s3 = Command::strSplit(s2[j], ',', &size3);

				x = std::stoi(s3[0]);
				y = std::stoi(s3[1]);

				isPointInside = Command::isInsideRectangle(x1, y1, x2, y2, x, y);

				if (isPointInside == false) {
					return;
				}

				polygon->add(new Point(x, y));

			}
		}
		if (i == 3) {

			color = new char[strlen(s1[i])];
			strcpy(color, s1[i]);
		}
	}
	polygon->setColor(color);
	std::cout << "-> polygon ";
	polygon->printToConsole();
	shapesWithin++;
	std::cout << "\n";
}

void Polygons::setColor(char* color)
{
	this->color = new char[strlen(color) + 1];
	strcpy(this->color, color);
}
