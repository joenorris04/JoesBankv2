#include <iostream>
#include <string>
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
				bool successfulDelete = 1;
				do {
					account.loadAccount(account.accountDetails);
					int userChoice2 = account.accountActions();
					if (userChoice2 == 1) { // deposit

					}
					else if (userChoice2 == 2) { // withdraw

					}
					else if (userChoice2 == 3) { // change details
						Account account;
						std::string detailToChange;
						std::cout << "Please choose what you would like to change from the options below:\n";
						do {
							std::cout << "(1) First name\n";
							std::cout << "(2) Second name\n";
							std::cout << "(3) Age\n";
							std::cout << "(4) Password\n";
							std::getline(std::cin >> std::ws, detailToChange);
							if (detailToChange != "1" && detailToChange != "2" && detailToChange != "3" && detailToChange != "4"){
								std::cout << "Please choose an option by entering one of the numbers shown in brackets.\n";
							}
						} while (detailToChange != "1" && detailToChange != "2" && detailToChange != "3" && detailToChange != "4");
						if (detailToChange == "1") {
							//account.accountDetails and account.accountIndex is stored and so is firstName secondName etc
							//store accountDetails, delete account, rewrite account with detail changed
							std::string newFirstName;
							std::string newAccountDetails;
							std::string oldAccountDetails;
							bool newFirstNameValidity;
							do {
								std::cout << "Please enter your new first name: ";
								std::getline(std::cin >> std::ws, newFirstName);
								newFirstNameValidity = account.checkFirstNameValidity(newFirstName);
							} while (newFirstNameValidity == 0);
							oldAccountDetails = account.accountDetails;
							oldAccountDetails.erase(account.startPosFirstName, account.lengthOfFirstName);
							newAccountDetails = account.accountDetails.insert(account.startPosFirstName, newFirstName);
							std::cout << newAccountDetails; // accountDetails is no longer stored in memory
							
							//account.deleteAccount();
						}
						else if (detailToChange == "2") { // change second name
							
						}
						else if (detailToChange == "3") { // change age
							
						}
						else { // change password
							
						}
					}
					else if (userChoice2 == 4) { // delete account
						successfulDelete = account.deleteAccount();
						if (successfulDelete) {
							std::cout << "Your account has been deleted permanently although we may still sell your data on the black market.\n";
							returnToHomescreen = 1;
						}
						else {
							std::cout << "You failed the confirmation.\n";
						}
					}
					else {
						returnToHomescreen = 1;
					}
				} while (successfulDelete == 0);
				
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