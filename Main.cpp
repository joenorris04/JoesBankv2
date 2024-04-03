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
						std::string detailToChange;
						std::cout << "Please choose what you would like to change from the options below:\n";
						do {
							std::cout << "(1) First name\n";
							std::cout << "(2) Second name\n";
							std::cout << "(3) Age\n";
							std::cout << "(4) Postcode\n";
							std::cout << "(5) Password\n";
							std::getline(std::cin >> std::ws, detailToChange);
							if (detailToChange != "1" && detailToChange != "2" && detailToChange != "3" && detailToChange != "4" && detailToChange != "5"){
								std::cout << "Please choose an option by entering one of the numbers shown in brackets.\n";
							}
						} while (detailToChange != "1" && detailToChange != "2" && detailToChange != "3" && detailToChange != "4" && detailToChange != "5");
						if (detailToChange == "1") { // change first name
							std::string newFirstName;
							std::string newAccountDetails;
							std::string tempAccountDetails;
							bool newFirstNameValidity;
							std::fstream myFile;
							do {
								std::cout << "Please enter your new first name: ";
								std::getline(std::cin >> std::ws, newFirstName);
								newFirstNameValidity = account.checkFirstNameValidity(newFirstName);
							} while (newFirstNameValidity == 0);
							tempAccountDetails = account.accountDetails;
							tempAccountDetails.erase(account.startPosFirstName, account.lengthOfFirstName);
							newAccountDetails = tempAccountDetails.insert(account.startPosFirstName, newFirstName);
							account.deleteAccount("DELETE ACCOUNT");
							myFile.open("Accounts.txt", std::ios::app);
							if (myFile.is_open()) {
								myFile << newAccountDetails;
								myFile.close();
								std::cout << "Your first name has been successfully changed.\n";
							}
							else {
								std::cout << "Failed to open file.\n";
								reloadAccount = 0;
								returnToHomescreen = 1;
							}
						}
						else if (detailToChange == "2") { // change second name
							std::string newSecondName;
							std::string newAccountDetails;
							std::string tempAccountDetails;
							bool newSecondNameValidity;
							std::fstream myFile;
							do {
								std::cout << "Please enter your new second name: ";
								std::getline(std::cin >> std::ws, newSecondName);
								newSecondNameValidity = account.checkSecondNameValidity(newSecondName);
							} while (newSecondNameValidity == 0);
							tempAccountDetails = account.accountDetails;
							tempAccountDetails.erase(account.startPosSecondName, account.lengthOfSecondName);
							newAccountDetails = tempAccountDetails.insert(account.startPosSecondName, newSecondName);
							account.deleteAccount("DELETE ACCOUNT");
							myFile.open("Accounts.txt", std::ios::app);
							if (myFile.is_open()) {
								myFile << newAccountDetails;
								myFile.close();
								std::cout << "Your second name has been successfully changed.\n";
							}
							else {
								std::cout << "Failed to open file.\n";
								reloadAccount = 0;
								returnToHomescreen = 1;
							}
							
						}
						else if (detailToChange == "3") { // change age
							std::string newAge;
							std::string newAccountDetails;
							std::string tempAccountDetails;
							bool newAgeValidity = 0;
							std::fstream myFile;
							do {
								std::cout << "Please enter your new age: ";
								std::getline(std::cin >> std::ws, newAge);
								for (int i = 0; i < newAge.length(); i++) {
									if (newAge[i] == ' ') {
										newAge.erase(i, 1);
										i--;
									}

								}
								for (int i = 0; i < newAge.length(); i++) {
									if (!isdigit(newAge[i])) {
										std::cout << "Your age should be written as a number.\n";
										break;
									}
									else {
										newAgeValidity = 1;
									}
								}
							} while (newAgeValidity == 0);
							int intNewAge = stoi(newAge);
							if (intNewAge < 18) {
								std::cout << "This is an invalid age.\n";
								return 0;
							}
							tempAccountDetails = account.accountDetails;
							tempAccountDetails.erase(account.startPosAge, account.lengthOfAge);
							newAccountDetails = tempAccountDetails.insert(account.startPosAge, newAge);
							account.deleteAccount("DELETE ACCOUNT");
							myFile.open("Accounts.txt", std::ios::app);
							if (myFile.is_open()) {
								myFile << newAccountDetails;
								myFile.close();
								std::cout << "Your age has been successfully changed.\n";
							}
							else {
								std::cout << "Failed to open file.\n";
								reloadAccount = 0;
								returnToHomescreen = 1;
							}
							
						}
						else if (detailToChange == "4") { // change postcode
							std::string newPostcode;
							std::string newAccountDetails;
							std::string tempAccountDetails;
							bool newPostcodeValidity;
							std::fstream myFile;
							std::cout << "Please enter your new postcode: ";
							std::getline(std::cin >> std::ws, newPostcode);
							for (int i = 0; i < newPostcode.length(); i++) {
								if (newPostcode[i] == ' ') {
									newPostcode.erase(i, 1);
								}

							}
							tempAccountDetails = account.accountDetails;
							tempAccountDetails.erase(account.startPosPostcode, account.lengthOfPostcode);
							newAccountDetails = tempAccountDetails.insert(account.startPosPostcode, newPostcode);
							account.deleteAccount("DELETE ACCOUNT");
							myFile.open("Accounts.txt", std::ios::app);
							if (myFile.is_open()) {
								myFile << newAccountDetails;
								myFile.close();
								std::cout << "Your postcode has been successfully changed.\n";
							}
							else {
								std::cout << "Failed to open file.\n";
								reloadAccount = 0;
								returnToHomescreen = 1;
							}
						}
						else { // change password
							std::fstream myFile;
							std::string newPassword1;
							std::string newPassword2;
							bool passwordValidity;
							std::string newAccountDetails;
							std::string tempAccountDetails;
							do {
								do {
									std::cout << "Please enter a new password: ";
									std::getline(std::cin >> std::ws, newPassword1);
									passwordValidity = account.checkPasswordValidity(newPassword1);
								} while (passwordValidity == 0);
								std::cout << "Please confirm your new password: ";
								std::getline(std::cin >> std::ws, newPassword2);
								if (newPassword1 == newPassword2) {
									int startPosPassword = account.lengthOfAccountDetails - account.lengthOfPassword;
									tempAccountDetails = account.accountDetails;
									tempAccountDetails.erase(startPosPassword, account.lengthOfPassword);
									newAccountDetails = tempAccountDetails.insert(startPosPassword, newPassword1);
									account.deleteAccount("DELETE ACCOUNT");
									myFile.open("Accounts.txt", std::ios::app);
									if (myFile.is_open()) {
										myFile << newAccountDetails;
										myFile.close();
										std::cout << "Your password has been successfully changed.\n";
									}
									else {
										std::cout << "Failed to open file.\n";
										reloadAccount = 0;
										returnToHomescreen = 1;
									}
								}
								else {
									std::cout << "Your passwords do not match.\n";
								}
							} while (newPassword1 != newPassword2);
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