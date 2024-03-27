#include "Account.h"
#include <iostream>
#include <string>
#include <ctime>

uint32_t Account::generateAccountNumber() { // add checks to ensure the number hasnt been used before

	uint32_t accountNumber;

	srand(time(NULL));
	std::string randomNumber1 = std::to_string(rand() & 9000 + 1000);

	srand(time(NULL) + 82735983); // maybe a better way to do this?
	std::string randomNumber2 = std::to_string(rand() & 9000 + 1000);
	
	std::string strAccountNumber = randomNumber1 + randomNumber2;
	accountNumber = stoi(strAccountNumber);

	return accountNumber;
}

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
	std::string inputFirstName;
	std::string inputSecondName;
	std::string inputPassword1;
	std::string inputPassword2;
	std::string inputPostcode;
	int inputAge;
	bool passwordValidity;
	bool x;
	bool y;
	std::cout << "Please enter your age: ";
	std::cin >> inputAge;
	if (inputAge < 18) {
		std::cout << "You are not old enough to create an account!";
	}
	else {
		do {
			std::cout << "Please enter your first name: ";
			std::getline(std::cin >> std::ws, inputFirstName);
			x = checkFirstNameValidity(inputFirstName);
		} while (x == 0);
		do {
			std::cout << "Please enter your second name: ";
			std::getline(std::cin >> std::ws, inputSecondName);
			y = checkSecondNameValidity(inputSecondName);
		} while (y == 0);

		std::cout << "Please enter your postcode: ";
		std::getline(std::cin >> std::ws, inputPostcode);
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
		firstName = inputFirstName;
		secondName = inputSecondName;
		age = inputAge;
		postcode = inputPostcode;
		accountNumber = generateAccountNumber();
		std::cout << "Below is your new account number. Please do not forget this!\n";
		std::cout << accountNumber;
	}
}


void Account::login() {
	std::cout << "I am logging in.";
}