#include "Command.h"


const char* Command::OPEN = "open";
const char* Command::PRINT = "print";
const char* Command::CREATE = "create";
const char* Command::WHITHIN = "whithin";
const char* Command::ERASE = "erase";
const char* Command::TRANSLATE = "translate";
const char* Command::SAVE = "saveD"; // will change later
const char* Command::SAVEAS = "save";
const char* Command::HELP = "help";
//const char* Command::EXIT = "exit";



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

void Command::createNewShape(std::fstream& file, char * shapeName)
{ 
	if (!file.is_open()) {
		std::cerr << "This file is not opened yet!" << std::endl <<
			"If you want to use it, please open it first!" << std::endl;

	}
	else {
	    
		if (strcmp(shapeName, Shape::CIRCLE) == 0) {

		}
		else if (strcmp(shapeName, Shape::ELLIPSE) == 0) {

		}
		else if (strcmp(shapeName, Shape::RECTANGLE) == 0) {

		}
		else if (strcmp(shapeName, Shape::LINE) == 0) {

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
	    while(file >> currLine && currLen++ < newLen) {
	        temp << currLine;
	    }

		temp << "\t" << shapeName << "\n</svg>"; // реално функцията
		file.close();
		temp.close();

		remove("figures.svg");
		rename("temp.svg", "figures.svg");
		file.open("figures.svg", std::ios::in | std::ios::out);

	}

}

void Command::whithin(std::fstream& file)
{
	if (!file.is_open()) {
		std::cerr << "This file is not opened yet!" << std::endl <<
			"If you want to use it, please open it first!" << std::endl;

	}
	else {}
}

void Command::eraseShape(std::fstream& file, int numOfShape)
{
	if (!file.is_open()) {
		std::cerr << "Can't erase anything, this file is not opened yet!" << std::endl <<
			"If you want to use it, please open it first!" << std::endl;

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
			file.getline(line, 100);
			if (currLine != numOfShape + 3) {
				temp << line << std::endl;
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

void Command::translate(std::fstream& file)
{
	if (!file.is_open()) {
		std::cerr << "This file is not opened yet!" << std::endl <<
			"If you want to use it, please open it first!" << std::endl;

	}
	else {}
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

