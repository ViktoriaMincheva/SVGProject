#include "Polylines.h"
#include <string>
#include <fstream>

Polylines::Polylines() 
{
	capacity = 1;
	curr = 0;
	points = new Point*[capacity];
}

Polylines::Polylines(int cap)
{
	capacity = cap;
	curr = 0;
	points = new Point*[capacity];
}

Polylines::Polylines(Point** ps, int cap)
{
	capacity = cap;
	curr = 0;
	points = new Point*[capacity];

	for (; curr < capacity; curr++) {
		points[curr] = new Point(ps[curr]->getX(), ps[curr]->getY());
	}
}

void Polylines::add(Point* point)
{
	points[curr] = new Point(point->getX(), point->getY());
	curr++;
}

Shape* Polylines::createPolyline(char* line)
{
	// create polyline 1 2 1 2 1 2 1 2 blue
	//1 2 3 4 5 6 blue
	int j = strlen(line);
	int lenght = j - 16;
	char* lineCopy = new char [lenght];
	
	int k = 0;
	for (int i = 16; i < j; i++) {
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
		std::cerr << "Invalid number of points! Polyline needs at least 3 points to be a polyline! " << std::endl;
		return nullptr;
	}

	char* token;
	token = strtok(lineCopy, " ");

	int val = 0, x, y, spaces = 0;
	char* color = new char[1];

	Polylines* polyline = new Polylines(numOfSpaces / 2);


	while (token != NULL) {
		
		if (spaces < numOfSpaces) {
			if (val % 2 == 0) { // chetno
				x = std::stoi(token);
				spaces++;
			}
			else if (val % 2 == 1) {
				y = std::stoi(token);
				spaces++;
				polyline->add(new Point(x, y));
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
	polyline->setColor(color);

	return polyline;
}
/*char** Polylines::strSplit(char* word, char delimiter, int* size) {
	int delimiters = 0;

	for (int i = 0; i < strlen(word); i++) {
		if (word[i] == delimiter) {
			delimiters++;
		}
	}

	*size = delimiters + 1;

	char** result = new char* [delimiters];

	char* token = strtok(word, &delimiter);

	int i = 0;
	while (token != NULL) {
		result[i] = new char[strlen(token) + 1];
		strcpy(result[i], token);
		i++;

		token = strtok(NULL, &delimiter);
	}

	return result;
}*/

Shape* Polylines::printPolyline(char* line)
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

	
	Polylines* polyline = new Polylines(numOfCommas);

	for (int i = 0; i < size1; i++) {
		if (i == 1) {
			
			int size2 = 0;
			char** s2 = Command::strSplit(s1[i], ' ', &size2);
			for (int j = 0; j < size2; j++) {
				int size3 = 0;
				char** s3 = Command::strSplit(s2[j], ',', &size3);

				x = std::stoi(s3[0]);
				y = std::stoi(s3[1]);
				polyline->add(new Point(x, y));
				
			}
		}
		if (i == 3) {
			color = new char[strlen(s1[i])];
			strcpy(color, s1[i]);
		}
	}
	polyline->setColor(color);

	return polyline;
}

void Polylines::printToConsole()
{
	
	for (int i = 0; i < capacity; i++) {
		std::cout << points[i]->getX() << "," << points[i]->getY() << " ";
	}
	Shape::printToConsole();

}

void Polylines::printToFile(std::fstream& file)
{
	file << "  <polyline points=\"";
	for (int i = 0; i < capacity; i++) {
		file << points[i]->getX() << "," << points[i]->getY();
		if (i == capacity - 1) {
			file << "\"";
		}
		else {
			file << " ";
		}
	}
	file << " stroke=\"";
	Shape::printToFile(file);
	file << "\" />";
}

void Polylines::translatePolyline(std::fstream& temp, char* lineFromFile, int verticalTr, int horizontalTr)
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


	Polylines* polyline = new Polylines(numOfCommas);

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
				polyline->add(new Point(x, y));

			}
		}
		if (i == 3) {
			color = new char[strlen(s1[i])];
			strcpy(color, s1[i]);
		}
	}
	polyline->setColor(color);

	polyline->printToFile(temp);
	temp << "\n";
}

void Polylines::polylineWithinCircle(char* lineFromFile, int circleX, int circleY, int radius, int* shapesWithin)
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


	Polylines* polyline = new Polylines(numOfCommas);
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

				polyline->add(new Point(x, y));

			}
		}
		if (i == 3) {
			color = new char[strlen(s1[i])];
			strcpy(color, s1[i]);
		}
	}
	polyline->setColor(color);
    *shapesWithin += 1;
	std::cout << "-> polyline ";
	polyline->printToConsole();
	
	std::cout << "\n";
}

void Polylines::polylineWithinRectnagle(char* lineFromFile, int x1, int y1, int x2, int y2, int* shapesWithin)
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


	Polylines* polyline = new Polylines(numOfCommas);
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

				polyline->add(new Point(x, y));

			}
		}
		if (i == 3) {
			color = new char[strlen(s1[i])];
			strcpy(color, s1[i]);
		}
	}
	polyline->setColor(color);
	*shapesWithin += 1;
	std::cout << "-> polyline ";
	polyline->printToConsole();

	std::cout << "\n";
}

void Polylines::setColor(char * color)
{
	this->color = new char[strlen(color) + 1];
	strcpy(this->color, color);
}

