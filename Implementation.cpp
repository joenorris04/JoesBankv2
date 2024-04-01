#include <iostream>
#include "Header.h"

bool firstLogin = 1;

std::string homeScreen() {
	std::string x;
	if (firstLogin) {
		std::cout << "Welcome to Joe's Bank. ";
		firstLogin = 0;
	}
	do {
		std::cout << "Please choose an option below.\n";
		std::cout << "(1) Create a new account.\n";
		std::cout << "(2) Login to an existing account.\n";
		std::cout << "(3) Exit Joe's Bank.\n";
		std::cin >> x;
		if (x != "1" && x != "2" && x != "3") {
			std::cout << "Please choose an option by entering one of the numbers shown within brackets.\n";
		}
	} while (x != "1" && x != "2" && x != "3");

	return x;
}