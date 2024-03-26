#include <iostream>

std::string homeScreen() {
	std::string x;
	do {
		std::cout << "Welcome to Joe's Bank. Would you like to:\n";
		std::cout << "(1) Create a new account.\n";
		std::cout << "(2) Login to an existing account.\n";
		std::cout << "(3) Exit Joe's Bank.\n";
		std::cin >> x;
	} while (x != "1" && x != "2" && x != "3");

	return x;
}