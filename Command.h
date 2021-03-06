#pragma once
#include <iostream>
#include <fstream>
#include <string.h>
#include "Shape.h"



class Command
{
public:
	static const char* OPEN;
	static const char* CLOSE;
	static const char* PRINT;
	static const char* CREATE;
	static const char* WITHIN;
	static const char* ERASE;
	static const char* TRANSLATE;
	static const char* SAVE;
	static const char* HELP;
	static const char* EXIT;

	static void openFile(std::fstream& file,char* fileName);
	static void closeFile(std::fstream& file,char* fileName);
	//static void printInfo(std::fstream& file);
	static void createNewShape(std::fstream& file, char * shapeName, char * line);
	static void within(std::fstream& file, char * line);
	static void eraseShape(std::fstream& file, int numOfShape);
	static void translate(std::fstream& file, char * line);
	static void save(std::fstream& file);
	static void saveas(std::fstream& file, char * newName);
	static void help();
	static void checkVertical(char* word, int* verticalTr, bool* shouldContinue);
	static void checkHorizontal(char* word, int* horizontalTr, bool* ifshouldContinue);
	static void translateOnlyOneShape(std::fstream& file, int shapeNum, int verticalTr, int horizontalTr);
	static void translateAllShapes(std::fstream& file, int verticalTr, int horizontalTr);
	static bool checkIfHasOnlyDigits(char*);
	static bool isInsideCircle(int, int, int, int, int);
	static bool isInsideRectangle(int, int, int, int, int, int);
	static void withinCircle(std::fstream&, char*);
	static void withinRectangle(std::fstream&, char*);
	static char** strSplit(char*, char, int*);

};

