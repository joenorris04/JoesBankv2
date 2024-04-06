#include <iostream>
#include <string>
#include <fstream>
#include "Header.h"
#include "Account.h"

int main() {

	bool returnToHomescreen = 0;

	do {
		std::string userChoice = homeScreen();
		int intUserChoice = stoi(userChoice);

		if (intUserChoice == 1) {
			Account account;
			if (account.getUserDetails()) {
				account.saveUserDetails(account.firstName, account.secondName, account.age, account.postcode, account.password, account.accountNumber);
			}
			returnToHomescreen = 1;
		}
		else if (intUserChoice == 2) {
			Account account;
			if (account.login()) {
				bool reloadAccount = 1;
				do {
					account.loadAccount(account.accountDetails);
					int userChoice2 = account.accountActions();
					if (userChoice2 == 1) { // deposit

					}
					else if (userChoice2 == 2) { // withdraw

					}
					else if (userChoice2 == 3) { // change details
						if (account.changeDetails() != 1) {
							reloadAccount = 0;
							returnToHomescreen = 1;
						}
					}
					else if (userChoice2 == 4) { // delete account
						std::string deleteConfirmation;
						bool successfulDelete;
						std::cout << "Please confirm you would like to delete your account by typing the following text identically:\n";
						std::cout << "DELETE ACCOUNT\n";
						getline(std::cin >> std::ws, deleteConfirmation);
						successfulDelete = account.deleteAccount(deleteConfirmation);
						if (successfulDelete) {
							std::cout << "Your account has been deleted permanently although we may still sell your data on the black market.\n";
							reloadAccount = 0;
							returnToHomescreen = 1;
						}
						else {
							std::cout << "You failed the confirmation.\n";
							reloadAccount = 0;
							returnToHomescreen = 1;
						}
					}
					else {
						reloadAccount = 0;
						returnToHomescreen = 1;
					}
				} while (reloadAccount == 1);
				
			}
			else {
				returnToHomescreen = 1;
			}
		}
		else {
			std::cout << "Thank you for using Joe's Bank!";
			break;
		}
	} while (returnToHomescreen == 1);

	return 0;
}