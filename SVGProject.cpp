#include <iostream>
#include <fstream>
#include <string>
#include "Command.h"
#include "Shape.h"

#define MAX_LINE 100

int main()
{
	char line[MAX_LINE];
	std::fstream file;

	while (true) {
		std::cin.getline(line, MAX_LINE);

		char* lineCop = new char[strlen(line) + 1];
		strcpy(lineCop, line);
		char* word = strtok(line, " ");
		bool hasOnlyDigits = true;

		if (word != NULL) {
			if (strcmp(word, Command::OPEN) == 0) { 
				char* fileName;
				fileName = strtok(NULL, " ");
				if (fileName == nullptr) {
					std::cerr << "Please give name to the file you want to open!\n\n";
				}
				else {
					Command::openFile(file, fileName);
					std::cout << "\n";
				}
			}
			else if (strcmp(word, Command::CLOSE) == 0) { 
				char* fileName;
				fileName = strtok(NULL, " ");
				Command::closeFile(file, fileName);
				std::cout << "\n";
			}
			else if (strcmp(word, Command::PRINT) == 0) { 

				if (!file.is_open()) {
					std::cerr << "This file is not opened yet!" << std::endl <<
						"If you want to use it, please open it first!" << std::endl;
					std::cout << "\n";
					continue;
				}
				char line[MAX_LINE];
				int currLine = 0;
				int toSkip = 4;
				int numOfShapes = 0;
				file.seekg(std::ios_base::beg);
				file.unsetf(std::ios::skipws);


				while (file) {
					file.getline(line, MAX_LINE);
					if (strcmp(line, "</svg>") == 0) {
						break;
					}
					if (currLine < toSkip) {
						currLine++;

						continue;
					}
					
					char* shapeName;
					char* lineCopy = new char[strlen(line) + 1];
					strcpy(lineCopy, line);
					shapeName = strtok(line, " ");
					numOfShapes++;

					Shape::printShape(lineCopy, shapeName, numOfShapes);
					

				}
				std::cout << "\n";
			}
			else if (strcmp(word, Command::CREATE) == 0) {
				
				char* shapeName;
				
				shapeName = strtok(NULL, " ");

				Command::createNewShape(file, shapeName, lineCop);

				std::cout << "\n";
			}
			else if (strcmp(word, Command::WITHIN) == 0) {

				Command::within(file, lineCop);
				std::cout << "\n";
			}
			else if (strcmp(word, Command::ERASE) == 0) { 
				char* token;
				token = strtok(NULL, " ");
				int numOfShape;

				if (Command::checkIfHasOnlyDigits(token) == false) {
					std::cerr << "Invalid operation! Erase should be followed by a number!\n";
				}
				else {
				numOfShape = std::stoi(token);
				Command::eraseShape(file, numOfShape);
			    }

				std::cout << "\n";
			}
			else if (strcmp(word, Command::TRANSLATE) == 0) {

				Command::translate(file, lineCop);
				std::cout << "\n";
			} 
			else if (strcmp(word, Command::EXIT) == 0) {
				file.close();
				std::cout << "Exit!" << std::endl;
				return 0;
			}
			else if (strcmp(word, Command::SAVE) == 0) {
				// save as shape.svg
				char* checkIfAs;
				checkIfAs = strtok(NULL, " ");
				
				if (checkIfAs == NULL) {
					Command::save(file);
				}
				else if (strcmp(checkIfAs, "as")==0) {
					char* newName;
					newName = strtok(NULL, " ");
					Command::saveas(file, newName);
				}
				else {
					std::cout << "Invalid command!" << std::endl;
				}
				std::cout << "\n";
			}
			else if (strcmp(word, Command::HELP) == 0) { 
				Command::help();
				std::cout << "\n";
			}
			else {
				std::cout << "Command not recognized! Try again!" << std::endl;
			}
		}
	}

	return 0;
}
