#pragma once
#include <iostream>
#include <fstream>
#include <string.h>
#include "Shape.h"



class Command
{
public:
	static const char* OPEN;
	static const char* PRINT;
	static const char* CREATE;
	static const char* WHITHIN;
	static const char* ERASE;
	static const char* TRANSLATE;
	static const char* SAVE;
	static const char* SAVEAS;
	static const char* HELP;
	//static const char* EXIT;

	static void openFile(std::fstream& file,char* fileName);
	//static void printInfo(std::fstream& file);
	static void createNewShape(std::fstream& file, char * shapeName);
	static void whithin(std::fstream& file);
	static void eraseShape(std::fstream& file, int numOfShape);
	static void translate(std::fstream& file);
	static void save(std::fstream& file);
	static void saveas(std::fstream& file, char * newName);
	static void help();
};

