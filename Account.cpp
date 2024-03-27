#include "Account.h"
#include <iostream>
#include <string>

bool Account::checkPasswordValidity(std::string inputPassword) {
	int passwordLength = inputPassword.length();
	if (passwordLength > 7) {
		for (int i = 0; inputPassword[i] != '\0'; i++) {
			bool x = isdigit(inputPassword[i]);
			if (x != 0) {
				return 1;
			}
		}
	}
	else {
		std::cout << "Your password must be a minimum of eight characters.\n";
		return 0;
	}
	std::cout << "Your password must contain a minimum of one number.\n";
	return 0;
}

bool Account::checkFirstNameValidity(std::string inputName) {
	int nameLength;
	for (int i = 0; inputName[i] != '\0'; i++) {
			bool x = isspace(inputName[i]);
			if (x == 1) {
				std::cout << "Ensure you only enter your first name with no spaces.\n";
				return 0;
			}
		
	}
	return 1;
}

bool Account::checkSecondNameValidity(std::string inputName) {
	int nameLength;
	for (int i = 0; inputName[i] != '\0'; i++) {
		bool x = isspace(inputName[i]);
		if (x == 1) {
			std::cout << "Ensure you only enter your second name with no spaces.\n";
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
	bool passwordValidity;
	bool x;
	bool y;
	std::cout << "Please enter your age: ";
	std::cin >> age;
	if (age < 18) {
		std::cout << "You are not old enough to create an account!";
	}
	else {
		do {
			std::cout << "Please enter your first name: ";
			std::getline(std::cin >> std::ws, firstName);
			x = checkFirstNameValidity(firstName);
		} while (x == 0);
		do {
			std::cout << "Please enter your second name: ";
			std::getline(std::cin >> std::ws, secondName);
			y = checkSecondNameValidity(secondName);
		} while (y == 0);

		std::cout << "Please enter your postcode: ";
		std::getline(std::cin >> std::ws, postcode);
		do {
			do {
				std::cout << "Please enter a password: ";
				std::cin >> inputPassword1;
				passwordValidity = checkPasswordValidity(inputPassword1);
			} while (passwordValidity == 0);
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