#include "Account.h"
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>

uint32_t Account::numberOfAccounts() {
	uint32_t numberOfAccounts = 0;
	std::string account;
	std::fstream myFile;
	myFile.open("Accounts.txt", std::ios::in);
	while (std::getline(myFile, account)) {
		numberOfAccounts++;
	}
	return numberOfAccounts;

}

bool Account::checkAccountNumberValidity(std::string inputAccountNumber) {
	int accountNumberLength = 0;
	for (int i = 0; inputAccountNumber[i] != '\0'; i++) {
		accountNumberLength++;
	}
	if (accountNumberLength == 19) {
		return 1;
	}
	else {
		return 0;
	}
}

std::string Account::generateAccountNumber() { // add checks to ensure the number hasnt been used before - 16 digit

	srand((unsigned int)time(NULL));

	int randomNumberBase = (rand() % 9000 + 1000);
	std::string strNum1 = std::to_string(randomNumberBase);

	int num2 = (randomNumberBase * randomNumberBase) % 9000 + 1000;
	std::string strNum2 = std::to_string(num2);

	int num3 = (num2 * num2) % 9000 + 1000;
	std::string strNum3 = std::to_string(num3);

	int num4 = (num3 * num3) % 9000 + 1000;
	std::string strNum4 = std::to_string(num4);

	std::string strAccountNumber = strNum1 + "-" + strNum2 + "-" + strNum3 + "-" + strNum4;

	return strAccountNumber;
}

bool Account::checkPasswordValidity(std::string inputPassword) {
	int passwordLength = inputPassword.length(); // size_t to unsigned int warning needs fix
	if (passwordLength > 7) {
		for (int i = 0; i < passwordLength; i++) {
			bool x = isdigit(inputPassword[i]);
			if (x != 0) {
				for (int j = 0; j < passwordLength; j++) {
					bool y = isspace(inputPassword[j]);
					if (y) {
						std::cout << "Your password cannot contain any spaces.\n";
						return 0;
					}
				}
				return 1;
			}
		}
		std::cout << "Your password must contain a minimum of one number.\n";
		return 0;
	}
	else {
		std::cout << "Your password must be a minimum of eight characters.\n";
		return 0;
	}
}

bool Account::checkFirstNameValidity(std::string inputName) {
	for (int i = 0; i < inputName.length(); i++) {
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
				std::getline(std::cin >> std::ws, inputPassword1);
				passwordValidity = checkPasswordValidity(inputPassword1);
			} while (passwordValidity == 0);
			std::cout << "Please confirm your password: ";
			std::getline(std::cin >> std::ws, inputPassword2);
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
		std::cout << accountNumber << '\n';
	}
}

void Account::saveUserDetails(std::string firstName, std::string secondName, int age, std::string postcode,std::string password, std::string accountNumber) {
	std::fstream myFile;
	myFile.open("Accounts.txt", std::ios::app);
	if (myFile.is_open()) {
		myFile << accountNumber << "    " << firstName << "    " << secondName << "    " << age << "    " << postcode << "    " << password << '\n';
		myFile.close();
	}
}


bool Account::login() {
	int lengthOfAccountDetails;
	int posOfAccountDetails;
	int matchingChars;
	int lengthOfPassword = 0;
	uint32_t accountsSearched = 0;
	std::string inputPassword;
	std::string inputAccountNumber;
	std::string accountDetails;
	bool accountNumberValidity = false;
	Account account;
	do {
		std::cout << "Please enter your account number in the format XXXX-XXXX-XXXX-XXXX\n";
		std::getline(std::cin >> std::ws, inputAccountNumber);
		accountNumberValidity = account.checkAccountNumberValidity(inputAccountNumber);
	} while (accountNumberValidity == false);
		std::fstream myFile;
		myFile.open("Accounts.txt", std::ios::in);
		if (myFile.is_open()) {
			uint32_t numberOfAccounts = account.numberOfAccounts();
			do {
				matchingChars = 0;
				getline(myFile, accountDetails);
				for (int i = 0; i < 19; i++) {
					if (inputAccountNumber[i] == accountDetails[i]) {
						matchingChars++;
					}
					else {
						break;
					}

				}
				accountsSearched++;
				if (accountsSearched == numberOfAccounts) {
					std::cout << "Your account number was not recognised.\n";
					return 0;
				}

			} while (matchingChars < 19);

			myFile.close();
			if (matchingChars == 19) {
				lengthOfAccountDetails = accountDetails.length();
				posOfAccountDetails = lengthOfAccountDetails - 1;
				do {
					posOfAccountDetails--;
					lengthOfPassword++;
				} while (accountDetails[posOfAccountDetails] != ' ');

				int startPos = lengthOfAccountDetails - lengthOfPassword;
				password = accountDetails.substr(startPos, lengthOfAccountDetails);

				std::cout << "Please enter your password: ";
				std::cin >> inputPassword;

				if (inputPassword == password) {
					std::cout << "Successful login!\n";
					return 1;
				}
				else {
					std::cout << "Incorrect Password.\n";
					return 0;
				}
			}
			else {
				"Account number was not recognised.\n";
				return 0;
			}


		}

		else {
			std::cout << "Failed to open file.\n";
			return 0;
		}
}


