#include "Account.h"
#include <iostream>
#include <string>


void Account::getUserDetails() {
	/*
	add checks for password length
	*/
	std::string inputFullName;
	std::string inputPassword1;
	std::string inputPassword2;
	int passwordLength;
	std::cout << "Please enter your age: ";
	std::cin >> age;
	if (age < 18) {
		std::cout << "You are not old enough to create an account!";
	}
	else {
		std::cout << "Please enter your full name: ";
		std::getline(std::cin >> std::ws, inputFullName); // need to create function to split into first, middle and last name
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
				std::cout << password;
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