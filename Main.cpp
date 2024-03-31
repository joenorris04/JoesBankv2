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
		account.saveUserDetails(account.firstName, account.secondName, account.age, account.postcode, account.password, account.accountNumber);
	}
	else if (intUserChoice == 2) {
		Account account;
		account.login();
	}
	else {
		std::cout << "Thank you for using Joe's Bank!";
	}

	return 0;
}