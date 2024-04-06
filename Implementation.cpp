#include <iostream>
#include <string>
#include "Header.h"


bool firstUse = 1;

std::string homeScreen() {
	std::string x;
	if (firstUse) {
		std::cout << "Welcome to Joe's Bank. ";
		std::cout << "Please choose an option below.\n";
		firstUse = 0;
	}
	do {
		std::cout << "(1) Create a new account.\n";
		std::cout << "(2) Login to an existing account.\n";
		std::cout << "(3) Exit Joe's Bank.\n";
		std::getline(std::cin >> std::ws, x);
		if (x != "1" && x != "2" && x != "3") {
			std::cout << "Please choose an option by entering one of the numbers shown within brackets.\n";
		}
	} while (x != "1" && x != "2" && x != "3");

	return x;
}
