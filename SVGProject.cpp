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

		char* word = strtok(line, " ");

		if (word != NULL) {
			if (strcmp(word, Command::OPEN) == 0) { //t.e. първата дума е open
				char* fileName;
				fileName = strtok(NULL, " ");
				Command::openFile(file, fileName);

			}
			else if (strcmp(word, Command::PRINT) == 0) {

				if (!file.is_open()) {
					std::cerr << "This file is not opened yet!" << std::endl <<
						"If you want to use it, please open it first!" << std::endl;
					continue;
				}
				char line[MAX_LINE];
				int currLine = 0;
				int toSkip = 4;
				int numOfShapes = 0;
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
					//std::cout << line << std::endl;
					char* shapeName;
					char* lineCopy = new char[strlen(line) + 1];
					strcpy(lineCopy, line);
					shapeName = strtok(line, " ");
					numOfShapes++;

					Shape::printShape(lineCopy, shapeName, numOfShapes);
					

				}
				
			}
			else if (strcmp(word, Command::CREATE) == 0) {
				
				char* shapeName;
				shapeName = strtok(NULL, " ");
				Command::createNewShape(file, shapeName);


			}
			else if (strcmp(word, Command::WHITHIN) == 0) {

				std::cout << Command::WHITHIN << std::endl;
			}
			else if (strcmp(word, Command::ERASE) == 0) {
				char* token;
				token = strtok(NULL, " ");

				int numOfShape;
				numOfShape = std::stoi(token);
				Command::eraseShape(file, numOfShape);


			}
			else if (strcmp(word, Command::TRANSLATE) == 0) {

				std::cout << Command::TRANSLATE << std::endl;
			}
			else if (strcmp(word, Command::SAVE) == 0) { // da pitam
				//char* fileName;
				//fileName = strtok(NULL, " ");
				Command::save(file);


				std::cout << Command::SAVE << std::endl;
			}
			else if (strcmp(word, "exit") == 0) { //done
				file.close;
				std::cout << "Exit!" << std::endl;
				return 0;
			}
			else if (strcmp(word, Command::SAVEAS) == 0) {
				// save as shape.svg
				char* checkIfAs;
				checkIfAs = strtok(NULL, " ");
				if (strcmp(checkIfAs, "as")==0) {
					char* newName;
					newName = strtok(NULL, " ");
					Command::saveas(file, newName);
				}
				else {
					std::cout << "Invalid command!" << std::endl;
				}
				
			}
			else if (strcmp(word, Command::HELP) == 0) { //done
				Command::help();
			}
			else {
				std::cout << "Command not recognized! Try again!" << std::endl;
			}


		}


	}


	



	return 0;
}
