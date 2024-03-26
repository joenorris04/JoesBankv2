#include "Account.h"
#include <iostream>
#include <string>

bool Account::checkNameValidity(std::string inputName) {
	int nameLength;
	for (int i = 0; inputName[i] != '\0'; i++) {
			bool x = isspace(inputName[i]);
			if (x == 1) {
				return 0;
			}
		
	}
	return 1;
}


void Account::getUserDetails() {
	std::string firstName;
	std::string secondName;
	std::string inputPassword1;
	std::string inputPassword2;
	int passwordLength;
	bool x;
	bool y;
	std::cout << "Please enter your age: ";
	std::cin >> age;
	if (age < 18) {
		std::cout << "You are not old enough to create an account!";
	}
	else {
		do {
			std::cout << "Please enter your first name with no spaces: ";
			std::getline(std::cin >> std::ws, firstName);
			x = checkNameValidity(firstName);
		} while (x == 0);
		do {
			std::cout << "Please enter your second name with no spaces: ";
			std::getline(std::cin >> std::ws, secondName);
			y = checkNameValidity(secondName);
		} while (y == 0);

		std::cout << "Please enter your postcode: ";
		std::getline(std::cin >> std::ws, postcode);
		do {
			do {
				std::cout << "Please enter a password that is a minimum of 8 characters: ";
				std::cin >> inputPassword1;
				passwordLength = inputPassword1.length();
			} while (passwordLength < 8);
			std::cout << "Please confirm your password: ";
			std::cin >> inputPassword2;
			if (inputPassword1 == inputPassword2) {
				password = inputPassword1;
			}
			else {
				std::cout << "Your passwords do not match.\n";
			}
		} while (inputPassword1 != inputPassword2);
	}
}


void Account::login() {
	std::cout << "I am logging in.";
}