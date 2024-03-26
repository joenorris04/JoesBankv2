#include <iostream>
#include <string>
#include "Header.h"
#include "Account.h"

int main() {


	std::string userChoice = homeScreen();
	int intUserChoice = stoi(userChoice);
	
	if (intUserChoice == 1) {
		Account account;
		account.getUserDetails();
	}
	else if (intUserChoice == 2) {
		Account account;
		account.login();
	}

	return 0;
}