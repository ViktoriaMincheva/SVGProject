#include "Command.h"
#include "Circles.h"
#include "Ellipses.h"
#include "Rectangles.h"
#include "StraightLines.h"
#include "Polygons.h"
#include "Polylines.h"



const char* Command::OPEN = "open";
const char* Command::CLOSE = "close";
const char* Command::PRINT = "print";
const char* Command::CREATE = "create";
const char* Command::WITHIN = "within";
const char* Command::ERASE = "erase";
const char* Command::TRANSLATE = "translate";
const char* Command::SAVE = "save"; 
const char* Command::HELP = "help";
const char* Command::EXIT = "exit";



void Command::openFile(std::fstream& file,char * fileName)
{
	file.open(fileName,std::ios::in | std::ios::out);

	if (!file.is_open()) {

		std::cerr << "Soryy, I couldn't open the file! Try again or type in: help!";
		
	}
	else {
		std::cout << "Successfully opened " << fileName << std::endl;
	}
}

void Command::closeFile(std::fstream& file, char* fileName)
{
	if (!file.is_open()) {
		std::cerr << "You can not close a file that it's not opened yet!" << std::endl;
		
	}
	else {
		file.close();
		std::cout << fileName << " is successfully closed!" << std::endl;
	}
}

void Command::createNewShape(std::fstream& file, char * shapeName, char * line)
{ 
	if (!file.is_open()) {
		std::cerr << "This file is not opened yet!" << std::endl <<
			"If you want to use it, please open it first!" << std::endl;
		std::cout << "\n";
	}
	else {
		Shape* shape = new Circles;
		if (strcmp(shapeName, Shape::CIRCLE) == 0) {
			shape = Circles::createCircle(line);
		}
		else if (strcmp(shapeName, Shape::ELLIPSE) == 0) {
			shape = Ellipses::createEllipse(line);
		}
		else if (strcmp(shapeName, Shape::RECTANGLE) == 0) {
			shape = Rectangles::createRectangle(line);
		}
		else if (strcmp(shapeName, Shape::LINE) == 0) {
			shape = StraightLines::createLine(line);
		}
		else if (strcmp(shapeName, Shape::POLYLINE) == 0) {
			shape = Polylines::createPolyline(line);
		}
		else if (strcmp(shapeName, Shape::POLYGON) == 0) {
			shape = Polygons::createPolygon(line);
		}
		else {
			std::cerr << "Invalid shape name!" << std::endl;
			std::cout << "You can only create the following shapes: " << std::endl <<
				"circle \t ellipse \t rectangle \t line \t polyline \t polygon" << std::endl;
			return;
		}

		if (shape == nullptr) {
			return;
		}

		file.seekg(std::ios_base::beg);
		file.unsetf(std::ios::skipws);
	    int length = 0;
	    char currLine;
		while (file >> currLine){
			length++;
		}
	    file.close();

	    file.open("figures.svg", std::ios_base::in);
	    file.unsetf(std::ios::skipws);
		std::fstream temp;
		temp.open("temp.svg", std::ios_base::out);

	    int newLen = length - 6; // махаме </svg>
	    file.seekg(std::ios_base::beg);

	    int currLen = 0;
	    while(file >> currLine && currLen < newLen) {
	        temp << currLine;
			currLen++;
	    }

		shape->printToFile(temp); 
		temp << "\n</svg>"; 
		file.close();
		temp.close();

		remove("figures.svg");
		if (rename("temp.svg", "figures.svg") != 0) {
			std::cerr << "Copy fail!!" << std::endl;
		}
		else {
			file.open("figures.svg", std::ios::in | std::ios::out);

			std::cout << "Successfully created " << shapeName << std::endl;
		}
	}

} 

void Command::within(std::fstream& file, char * line)
{
	if (!file.is_open()) {
		std::cerr << "This file is not opened yet!" << std::endl <<
			"If you want to use it, please open it first!" << std::endl;
		std::cout << "\n";
	}
	else {
		char* lineCopy = new char[strlen(line) + 1];
		strcpy(lineCopy, line);


		char* token;
		token = strtok(line, " ");

		while (token != NULL) {
			if (strcmp(token, "within") == 0) {
			}
			else if (strcmp(token, "circle") == 0) {
				Command::withinCircle(file, lineCopy);
				break;
			}
			else if (strcmp(token, "rectangle") == 0) {
				Command::withinRectangle(file, lineCopy);
				break;
			}
			else {
				std::cerr << "Invalid shape, I can only check within circle or rectangle!" << std::endl;
				return;
			}
			token = strtok(NULL, " ");
		}

	}
}

void Command::eraseShape(std::fstream& file, int numOfShape)
{
	if (!file.is_open()) {
		std::cerr << "Can't erase anything, this file is not opened yet!" << std::endl <<
			"If you want to use it, please open it first!" << std::endl;
		std::cout << "\n";
	}
	else {
		char line[100];
		file.seekg(std::ios_base::beg);
		file.unsetf(std::ios::skipws);
		int currLine = 0;
		int allLines = 0;

		std::fstream temp;
		temp.open("temp.svg", std::ios_base::out);

		while (file) {
			file.getline(line, 100);
			if (strcmp(line, "</svg>") == 0) {
				allLines++;
				break;
			}
			else {
				allLines++;
			}
		}

		if (allLines - 1 < numOfShape + 4) {
			std::cout << "There is no figure number " << numOfShape << "!" << std::endl;
			return;
		}

		file.seekg(std::ios_base::beg);
		file.unsetf(std::ios::skipws);

		while (file) {
			file.getline(line, 100); //DOBAVQM TUUUK
			if (currLine != numOfShape + 3) {
				if (strcmp(line, "</svg>") == 0) {
					temp << line;
					break;
				}
				else {
					temp << line << std::endl;
				}
			}
			if (currLine == numOfShape + 3) {
			}
			currLine++;
		}

		temp.close();
		file.close();

		remove("figures.svg");
		if (rename("temp.svg", "figures.svg") != 0) {
			std::cerr << "Copy fail!!" << std::endl;
		}
		else {
			file.open("figures.svg", std::ios::in | std::ios::out);

			std::cout << "Successfully erased shape " << numOfShape << std::endl;
		}

	}
}

void Command::translate(std::fstream& file, char* line)
{
	if (!file.is_open()) {
		std::cerr << "This file is not opened yet!" << std::endl <<
			"If you want to use it, please open it first!" << std::endl;
		std::cout << "\n";
	}
	else {
		char* lineCopy = new char[strlen(line) + 1];
		strcpy(lineCopy, line);
		char* lineCopy2 = new char[strlen(line) + 1];
		strcpy(lineCopy2, line);

		int tokenCount = 0;
		char* token;
		token = strtok(line, " ");
		int shapeNum;


		while (token != NULL) { //proverqva kolko tokena ima vyvedeni
			tokenCount++;
			token = strtok(NULL, " ");
		}
		std::cout << "\n";
		tokenCount--;

		if (tokenCount < 2 || tokenCount > 4) {
			std::cerr << "Invalid translate operation! \n" <<
				"Follow the example: \n" <<
				"If you want to translate only one shape:  translate <shapeNumber> vertical=<number> horizontal=<number> \n" <<
				"If you want to translate all shapes:      translate vertical=<number> horizontal=<number> \n" << std::endl;
		}
		else if (tokenCount == 2) { // translate vertical=12 horizontal=15
			char* word;

			int count = 0;
			int verticalTr = 0;
			int horizontalTr = 0;

			bool hasOnlyDigits = true;
			bool shouldContinue = true;

			word = strtok(lineCopy, " ");

			while (word != NULL) {
				if (count < 1) {
					count++;
				}
				else if (count == 1) {
					Command::checkVertical(word, &verticalTr, &shouldContinue);
					if (shouldContinue == false) {
						break;
					}
					count++;
				}
				else if (count == 2) {
					Command::checkHorizontal(word, &horizontalTr, &shouldContinue);
					if (shouldContinue == false) {
						break;
					}
					count++;
				}
				else if (count > 2) {
					break;
				}
				word = strtok(NULL, " ");
			}

			if (shouldContinue == false) {
				return;
			}

			Command::translateAllShapes(file, verticalTr, horizontalTr);
		}
		else if (tokenCount == 3) {
			char* word;
			word = strtok(lineCopy, " ");
			int count = 0;
			int verticalTr = 0;
			int horizontalTr = 0;
			bool hasOnlyDigits = true;
			bool shouldContinue = true;

			while (word != NULL) {
				if (count < 1) {
					count++;
				}
				else if (count == 1) {
					int length;
					length = strlen(word);
					
					for (int i = 0; i < length; i++) {
						if (!isdigit(word[i])) {
							hasOnlyDigits = false;
							break;
						}
					}
					if (hasOnlyDigits == false) {
						std::cout << "If you want to translate only one shape use this:  translate <shapeNumber> vertical=<number> horizontal=<number> \n" <<
							"<shapeNumber> must be a valid number! \n" << std::endl;
						shouldContinue = false;
						return;
					}

					shapeNum = std::stoi(word);
					count++;
				}
				else if (count == 2) {
					Command::checkVertical(word, &verticalTr, &shouldContinue);
					if (shouldContinue == false) {
						break;
					}
					count++;
				}
				else if (count == 3) {
					Command::checkHorizontal(word, &horizontalTr, &shouldContinue);
					if (shouldContinue == false) {
						break;
					}

					count++;
				}
				else if (count > 3) {
					break;
				}

				word = strtok(NULL, " ");
			}

			if (shouldContinue == false) {
				return;
			}
			Command::translateOnlyOneShape(file, shapeNum, verticalTr, horizontalTr);
		}
	}
}

void Command::save(std::fstream& file)
{
	if (!file.is_open()) {
		std::cerr << "This file is not opened yet!" << std::endl <<
			"If you want to use it, please open it first!" << std::endl;

	}
	else {
		std::cout << "Successfully saved the changes!" << std::endl;
	}
}

void Command::saveas(std::fstream& file, char* newName)
{
	if (!file.is_open()) {
		std::cerr << "This file is not opened yet!" << std::endl <<
			"If you want to use it, please open it first!" << std::endl;
	}
	else {
		char line[100];
		file.seekg(std::ios_base::beg);
		file.unsetf(std::ios::skipws);

		std::fstream newFile;
		newFile.open(newName, std::ios_base::out);

		while (file) {
			file.getline(line, 100);
			if (strcmp(line, "</svg>") == 0) {
				newFile << line;
				break;
			}
			else {
				newFile << line << std::endl;
			}
		}

		std::cout << "Successfully saved as " << newName << std::endl;
		newFile.close();
	}
}

void Command::help()
{
	std::cout << "You can only use the following commands: " << std::endl 
		      << "open <fileName>             | file opens\n" 
		      << "print                       | prints all of the shapes from file\n"
		      << "create  <shapeSpecifics>    | creates new shape\n" 
		      << "\t - circle x y r color\n"
		      << "\t - rectangle x y width height color\n"
		      << "\t - ellipse cx cy rx ry color\n"
		      << "\t - line x1 y1 x2 y2 color\n"
		      << "\t - polyline x1 y1 x2 y2 ... color\n"
		      << "\t - polygon x1 y1 x2 y2 ... color\n"
		      << "whithin <shape>             | checks if there is a shape whithin this shape\n"
		      << "erase <numOfShapeToErase>   | erases this shape\n"  
		      << "translate                   | transaltes 1 shape or all shapes\n" 
		      << "\t - translate only one shape:     translate <shapeNumber> vertical=<number> horizontal=<number> \n" 
		      << "\t - translate all shapes:         translate vertical=<number> horizontal=<number> \n"
		      << "save                        | saves the changes\n" 
		      << "save as <newFileName>       | saves the file under a new name\n" 
		      << "close <fileName>            | file closes\n"
		      << "help                        | this information\n" 
		      << "exit                        | exits the program\n";
}

void Command::checkVertical(char* word, int* verticalTr, bool* shouldContinue)
{
	bool hasOnlyDigits = true;
	char checkVertical[] = "vertical=";
	char* vertical = new char[1];
	vertical = new char[strlen(word) + 1];
	strcpy(vertical, word);

	for (size_t i = 0; i < strlen(checkVertical); i++) { //този for само проверява дали първите 8(9) знака са същите като checkVertical
		if (checkVertical[i] == vertical[i]) {
			continue;
		}
		else {
			std::cerr << "Invalid vertical input!\nMust be: translate <shapeNumber> vertical=<number> horizontal=<number> \n" << std::endl;
			*shouldContinue = false;
			return;
		}
	}
	char* num = new char[1];
	num = new char[strlen(vertical) - 9]; // - 7 за да махна първите 8 char-a, но 1 за терминиращата нула
	int k = 0; // брояч за num

	for (size_t j = 9; j < strlen(vertical); j++) {
		num[k] = vertical[j];
		k++;
	}
	num[k] = '\0';


	for (size_t i = 0; i < strlen(num); i++) {
		if (num[0] == '-') {
			continue;
		}
		if (!isdigit(num[i])) {
			hasOnlyDigits = false;
			break;
		}

	}

	if (hasOnlyDigits == false) {
		std::cerr << "vertical= must be followed by a number! " << std::endl << std::endl;
		*shouldContinue = false;
		return;
	}

	*verticalTr = std::stoi(num);

}

void Command::checkHorizontal(char* word, int* horizontalTr, bool* shouldContinue)
{
	bool hasOnlyDigits = true;
	char checkHorizontal[] = "horizontal=";
	char* horizontal = new char[1];
	horizontal = new char[strlen(word) + 1];
	strcpy(horizontal, word);
	bool isDigit = true;

	for (size_t i = 0; i < strlen(checkHorizontal); i++) {
		if (checkHorizontal[i] == horizontal[i]) {
			continue;
		}
		else {
			std::cerr << "Invalid horizontal input!\nMust be: translate <shapeNumber> vertical=<number> horizontal=<number> \n" << std::endl;
			*shouldContinue = false;
			return;
		}
	}

	int k = 0; // брояч за num
	char* num = new char[1];
	num = new char[strlen(horizontal) - 10]; // - 9 за да махна първите 10 char-a, но -1 за терминиращата нула

	for (size_t j = 11; j < strlen(horizontal); j++) {
		num[k] = horizontal[j];
		k++;
	}
	num[k] = '\0';


	for (size_t i = 0; i < strlen(num); i++) {
		if (num[0] == '-') {
			continue;
		}
		if (!isdigit(num[i])) {
			isDigit = false;
			break;
		}
	}

	if (isDigit == false) {
		std::cerr << "horizontal= must be followed by a number!" << std::endl << std::endl;
		*shouldContinue = false;
		return;
	}

	*horizontalTr = std::stoi(num);

}

void Command::translateOnlyOneShape(std::fstream& file, int shapeNum, int verticalTr, int horizontalTr)
{
	char lineFromFile[100];
	file.seekg(std::ios_base::beg);
	file.unsetf(std::ios::skipws);
	int currLine = 0;

	std::fstream temp;
	temp.open("temp.svg", std::ios_base::out);

	while (file) {

		file.getline(lineFromFile, 100); 

		if (currLine != shapeNum + 3) {
			if (strcmp(lineFromFile, "</svg>") == 0) {
				temp << lineFromFile;
				break;
			}
			else {
				temp << lineFromFile << std::endl;
			}
		}
		if (currLine == shapeNum + 3) {
			char* lineCopy = new char[strlen(lineFromFile) + 1];
			strcpy(lineCopy, lineFromFile);

			char* token = strtok(lineCopy, " ");

			if (strcmp(token, "<circle") == 0) { 
				Circles::translateCircle(temp, lineFromFile, verticalTr, horizontalTr);
			}
			else if (strcmp(token, "<rect") == 0) {
				Rectangles::translateRectangle(temp, lineFromFile, verticalTr, horizontalTr);
			}
			else if (strcmp(token, "<ellipse") == 0) {
				Ellipses::translateEllipse(temp, lineFromFile, verticalTr, horizontalTr);
			}
			else if (strcmp(token, "<line") == 0) {
				StraightLines::translateLine(temp, lineFromFile, verticalTr, horizontalTr);
			}
			else if (strcmp(token, "<polyline") == 0) {
				Polylines::translatePolyline(temp, lineFromFile, verticalTr, horizontalTr);
			}
			else if (strcmp(token, "<polygon") == 0) {
				Polygons::translatePolygon(temp, lineFromFile, verticalTr, horizontalTr);
			}
		}
		currLine++;
	}

	temp.close();
	file.close();

	remove("figures.svg");

	if (rename("temp.svg", "figures.svg") != 0) {
		std::cerr << "Copy fail!!" << std::endl;
	}
	else {
		file.open("figures.svg", std::ios::in | std::ios::out);

		std::cout << "Successfully translated shape " << shapeNum << std::endl;
	}

}

void Command::translateAllShapes(std::fstream& file, int verticalTr, int horizontalTr)
{
	char lineFromFile[100];
	file.seekg(std::ios_base::beg);
	file.unsetf(std::ios::skipws);
	int currLine = 0;

	std::fstream temp;
	temp.open("temp.svg", std::ios_base::out);

	while (file) {

		file.getline(lineFromFile, 100);

		if (currLine < 4) {
			temp << lineFromFile << std::endl;
		}
		else if (strcmp(lineFromFile, "</svg>") == 0) {
			temp << lineFromFile;
			break;
		}
		else {
			char* lineCopy = new char[strlen(lineFromFile) + 1];
			strcpy(lineCopy, lineFromFile);

			char* token = strtok(lineCopy, " ");

			if (strcmp(token, "<circle") == 0) { 
				Circles::translateCircle(temp, lineFromFile, verticalTr, horizontalTr);
			}
			else if (strcmp(token, "<rect") == 0) {
				Rectangles::translateRectangle(temp, lineFromFile, verticalTr, horizontalTr);
			}
			else if (strcmp(token, "<ellipse") == 0) {
				Ellipses::translateEllipse(temp, lineFromFile, verticalTr, horizontalTr);
			}
			else if (strcmp(token, "<line") == 0) {
				StraightLines::translateLine(temp, lineFromFile, verticalTr, horizontalTr);
			}
			else if (strcmp(token, "<polyline") == 0) {
				Polylines::translatePolyline(temp, lineFromFile, verticalTr, horizontalTr);
			}
			else if (strcmp(token, "<polygon") == 0) {
				Polygons::translatePolygon(temp, lineFromFile, verticalTr, horizontalTr);
			}
		}
		currLine++;
	}

	temp.close();
	file.close();

	remove("figures.svg");

	if (rename("temp.svg", "figures.svg") != 0) {
		std::cerr << "Copy fail!!" << std::endl;
	}
	else {
		file.open("figures.svg", std::ios::in | std::ios::out);

		std::cout << "Successfully translated all shapes " << std::endl;
	}
}

bool Command::checkIfHasOnlyDigits(char* token)
{
	for (size_t i = 0; i < strlen(token); i++) {
		if (!isdigit(token[i])) {
			return false;
		} else {
			continue;
		}
	}
	return true;
}

bool Command::isInsideCircle(int circleX, int circleY, int radius, int x, int y)
{
	if ((x - circleX) * (x - circleX) + (y - circleY) * (y - circleY) <= radius * radius) {
		return true;
	}
	else {
		return false;
	}
}

bool Command::isInsideRectangle(int x1, int y1, int x2, int y2, int x, int y)
{
	if (x > x1 && x < x2 && y > y1 && y < y2) {
		return true;
	}
	else {
		return false;
	}
}

void Command::withinCircle(std::fstream& file, char* line)
{
	char* lineCopy = new char[strlen(line) + 1];
	strcpy(lineCopy, line); 

	char* token;
	token = strtok(line, " ");

	int val = 0;
	int circleX = 0, circleY = 0, radius = 0;

	while (token != NULL) {
		if (val < 2) {
			val++;
		}
		else if (val == 2) {
			circleX = std::stoi(token);
			val++;
		}
		else if (val == 3) {
			circleY = std::stoi(token);
			val++;
		}
		else if (val == 4) {
			radius = std::stoi(token);
			val++;
		}
		token = strtok(NULL, " ");
	}

	char lineFromFile[100];
	file.seekg(std::ios_base::beg);
	file.unsetf(std::ios::skipws);
	int currLine = 0;
	int shapesWithin = 0;

	while (file) {

		file.getline(lineFromFile, 100);
		if (currLine < 4) {
		}
		else if (strcmp(lineFromFile, "</svg>") == 0) {
			break;
		}
		else {
			char* lineCopy = new char[strlen(lineFromFile) + 1];
			strcpy(lineCopy, lineFromFile);

			char* token = strtok(lineCopy, " ");
			
			if (strcmp(token, "<circle") == 0) { 
				Circles::circleWithinCircle(lineFromFile, circleX, circleY, radius, &shapesWithin);
			}
			else if (strcmp(token, "<rect") == 0) {
				Rectangles::rectangleWithinCircle(lineFromFile, circleX, circleY, radius, &shapesWithin);
			}
			else if (strcmp(token, "<ellipse") == 0) {
				Ellipses::ellipseWithinCircle(lineFromFile, circleX, circleY, radius, &shapesWithin);
			}
			else if (strcmp(token, "<line") == 0) {
				StraightLines::lineWithinCircle(lineFromFile, circleX, circleY, radius, &shapesWithin);
			}
			else if (strcmp(token, "<polyline") == 0) {
				Polylines::polylineWithinCircle(lineFromFile, circleX, circleY, radius, &shapesWithin);
			}
			else if (strcmp(token, "<polygon") == 0) {
				Polygons::polygonWithinCircle(lineFromFile, circleX, circleY, radius, &shapesWithin);
			}
		}

		currLine++;
	}
	if (shapesWithin == 0) {
		std::cout << "No figures are located " << lineCopy << std::endl;
	}
}

void Command::withinRectangle(std::fstream& file, char* line)
{
	char* lineCopy = new char[strlen(line) + 1];
	strcpy(lineCopy, line);

	char* token;
	token = strtok(line, " ");

	int val = 0;
	int x = 0, y = 0, width = 0, height = 0;
	
	while (token != NULL) {
		if (val < 2) {
			val++;
		}
		else if (val == 2) {
			x = std::stoi(token);
			val++;
		}
		else if (val == 3) {
			y = std::stoi(token);
			val++;
		}
		else if (val == 4) {
			width = std::stoi(token);
			val++;
		}
		else if (val == 5) {
			height = std::stoi(token);
			val++;
		}
		token = strtok(NULL, " ");
	}

	char lineFromFile[100];
	file.seekg(std::ios_base::beg);
	file.unsetf(std::ios::skipws);
	int currLine = 0;
	int shapesWithin = 0;

	while (file) {

		file.getline(lineFromFile, 100);
		if (currLine < 4) {
		}
		else if (strcmp(lineFromFile, "</svg>") == 0) {
			break;
		}
		else {
			char* lineCopy = new char[strlen(lineFromFile) + 1];
			strcpy(lineCopy, lineFromFile);

			char* token = strtok(lineCopy, " ");

			if (strcmp(token, "<circle") == 0) {
				Circles::circleWithinRectangle(lineFromFile, x, y, x+width, y+height, &shapesWithin);
			}
			else if (strcmp(token, "<rect") == 0) {
				Rectangles::rectangleWithinRectangle(lineFromFile, x, y, x + width, y + height, &shapesWithin);
			}
			else if (strcmp(token, "<ellipse") == 0) {
				Ellipses::ellipseWithinRectangle(lineFromFile, x, y, x + width, y + height, &shapesWithin);
			}
			else if (strcmp(token, "<line") == 0) {
				StraightLines::lineWithinRectangle(lineFromFile, x, y, x + width, y + height, &shapesWithin);
			}
			else if (strcmp(token, "<polyline") == 0) {
				Polylines::polylineWithinRectnagle(lineFromFile, x, y, x + width, y + height, &shapesWithin);
			}
			else if (strcmp(token, "<polygon") == 0) {
				Polygons::polygonWithinRectangle(lineFromFile, x, y, x + width, y + height, &shapesWithin);
			}
		}

		currLine++;
	}
	if (shapesWithin == 0) {
		std::cout << "No figures are located " << lineCopy << std::endl;
	}

}

char** Command::strSplit(char* word, char delimiter, int* size)
{
	int delimiters = 0;

	for (size_t i = 0; i < strlen(word); i++) {
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
}
