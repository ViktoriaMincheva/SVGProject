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
const char* Command::WHITHIN = "whithin";
const char* Command::ERASE = "erase";
const char* Command::TRANSLATE = "translate";
const char* Command::SAVE = "saveD"; // will change later
const char* Command::SAVEAS = "save";
const char* Command::HELP = "help";
const char* Command::EXIT = "exit";



void Command::openFile(std::fstream& file,char * fileName)
{
	file.open(fileName,std::ios::in | std::ios::out);

	if (!file.is_open()) {

		std::cerr << "Soryy, I couldn't open the file! Try again or type in: help!" << std::endl;
		
		
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

		}
		else if (strcmp(shapeName, Shape::POLYGON) == 0) {

		}
		else {
			std::cerr << "Invalid shape name!" << std::endl;
			std::cout << "You can only create the following shapes: " << std::endl <<
				"circle \t ellipse \t rectangle \t line \t polyline \t polygon" << std::endl;
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

		shape->printToFile(temp); //
		temp << "\n</svg>"; // реално функцията
		file.close();
		temp.close();

		remove("figures.svg");
		rename("temp.svg", "figures.svg");
		file.open("figures.svg", std::ios::in | std::ios::out);

		std::cout << "Successfully created " << shapeName << std::endl;
	}

}

void Command::whithin(std::fstream& file)
{
	if (!file.is_open()) {
		std::cerr << "This file is not opened yet!" << std::endl <<
			"If you want to use it, please open it first!" << std::endl;
		std::cout << "\n";
	}
	else {}
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

		std::fstream temp;
		temp.open("temp.svg", std::ios_base::out);

		// проверка, ако не съществува такава фигура

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
		rename("temp.svg", "figures.svg");
		file.open("figures.svg", std::ios::in | std::ios::out);

		std::cout << "Successfully erased shape " << numOfShape << std::endl;

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
			//std::cout << token << "   " << tokenCount << std::endl;
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
					//shouldContinue = true;
					Command::checkVertical(word, &verticalTr, &shouldContinue);
					if (shouldContinue == false) {
						break;
					}

					count++;
				}
				else if (count == 2) {
					//shouldContinue = true;
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
					//shouldContinue = true;
					Command::checkVertical(word, &verticalTr, &shouldContinue);
					if (shouldContinue == false) {
						break;
					}
					count++;
				}
				else if (count == 3) {
					//shouldContinue = true;

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
			//std::cout << "\n" << "emi ver e: " << verticalTr << "\n";
			//std::cout << "\n" << "emi hor e: " << horizontalTr << "\n";
			//std::cout << "\n" << "emi shape e: " << shapeNum << "\n";
			//std::cout << "funkciika" << std::endl << std::endl;
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
			newFile << line << std::endl;
		}

		std::cout << "Successfully saved as " << newName << std::endl;
		newFile.close();

		
	}
}

void Command::help()
{
	std::cout << "You can only use the following commands: " << std::endl 
		      << "open <fileName> \t print \t create \t whithin \t erase <numOfShapeToErase>\t" << std::endl 
		      << "translate \t save \t save as <newFileName> \t help \t exit \t" << std::endl;
}

void Command::checkVertical(char* word, int* verticalTr, bool* shouldContinue)
{
	bool hasOnlyDigits = true;
	char checkVertical[] = "vertical=";
	char* vertical = new char[1];
	vertical = new char[strlen(word) + 1];
	strcpy(vertical, word);

	for (int i = 0; i < strlen(checkVertical); i++) { //този for само проверява дали първите 8(9) знака са същите като checkVertical
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

	for (int j = 9; j < strlen(vertical); j++) {
		num[k] = vertical[j];
		k++;
	}
	num[k] = '\0';


	for (int i = 0; i < strlen(num); i++) {
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

	for (int i = 0; i < strlen(checkHorizontal); i++) {
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

	for (int j = 11; j < strlen(horizontal); j++) {
		num[k] = horizontal[j];
		k++;
	}
	num[k] = '\0';


	for (int i = 0; i < strlen(num); i++) {
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

		file.getline(lineFromFile, 100); // първи ред от файла


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

			if (strcmp(token, "<circle") == 0) { // тук може това да е функция в circle
				char* tok;
				tok = strtok(lineFromFile, "\"");

				int val = 0;
				int toSkip = 0;
				int x = 0, y = 0, r = 0;
				char* circleColor = new char[1];

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
							r = std::stoi(tok);
							val++;
						}
						else if (val == 3) {
							circleColor = new char[strlen(tok) + 1];
							strcpy(circleColor, tok);
							val++;
						}
					}
					toSkip++;
					tok = strtok(NULL, "\"");

				}
				temp << "  <circle cx=\"" << x << "\" cy=\"" << y << "\" r=\"" << r << "\" fill=\"" << circleColor << "\" />\n";
			}
			else if (strcmp(token, "<rect") == 0) {
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
			else if (strcmp(token, "<ellipse") == 0) {
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
			else if (strcmp(token, "<line") == 0) {
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
			else if (strcmp(token, "<polyline") == 0) {
				std::cout << "polyline" << std::endl;
			}
			else if (strcmp(token, "<polygon") == 0) {
				std::cout << "polygon" << std::endl;
			}

		}
		currLine++;
	}


	temp.close();
	file.close();

	remove("figures.svg");
	rename("temp.svg", "figures.svg");
	file.open("figures.svg", std::ios::in | std::ios::out);

	std::cout << "Successfully translated shape " << shapeNum << std::endl;
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

			if (strcmp(token, "<circle") == 0) { // тук може това да е функция в circle
				char* tok;
				tok = strtok(lineFromFile, "\"");

				int val = 0;
				int toSkip = 0;
				int x = 0, y = 0, r = 0;
				char* circleColor = new char[1];

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
							r = std::stoi(tok);
							val++;
						}
						else if (val == 3) {
							circleColor = new char[strlen(tok) + 1];
							strcpy(circleColor, tok);
							val++;
						}
					}
					toSkip++;
					tok = strtok(NULL, "\"");

				}
				temp << "  <circle cx=\"" << x << "\" cy=\"" << y << "\" r=\"" << r << "\" fill=\"" << circleColor << "\" />\n";
			}
			else if (strcmp(token, "<rect") == 0) {
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
			else if (strcmp(token, "<ellipse") == 0) {
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
			else if (strcmp(token, "<line") == 0) {
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
			else if (strcmp(token, "<polyline") == 0) {
				std::cout << "polyline" << std::endl;
			}
			else if (strcmp(token, "<polygon") == 0) {
				std::cout << "polygon" << std::endl;
			}


		}
		currLine++;
	}

	temp.close();
	file.close();

	remove("figures.svg");
	rename("temp.svg", "figures.svg");
	file.open("figures.svg", std::ios::in | std::ios::out);

	std::cout << "Successfully translated all shapes " << std::endl;
}