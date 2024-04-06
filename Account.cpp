#include "Account.h"
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>

#define MAX_ACCOUNTS 100 //can be changed to allow for more users

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

bool Account::getUserDetails() {
	std::string inputFirstName;
	std::string inputSecondName;
	std::string inputPassword1;
	std::string inputPassword2;
	std::string inputPostcode;
	std::string inputAge;
	int intInputAge;
	bool passwordValidity;
	bool ageValidity = 1;
	bool firstNameValidity;
	bool secondNameValidity;
	do {
		std::cout << "Please enter your age: ";
		std::getline(std::cin >> std::ws, inputAge);
		for (int i = 0; i < inputAge.length(); i++) {
			if (inputAge[i] == ' ') {
				inputAge.erase(i, 1);
				i--; // if a space is erased we must decrement i by 1 as the length of the string has been reduced
			}

		}
		for (int i = 0; i < inputAge.length(); i++) {
			if (!isdigit(inputAge[i])) {
				ageValidity = 0;
				std::cout << "Your age should be written as a number.\n";
				break;
			}
			else {
				ageValidity = 1;
			}
		}
	} while (ageValidity == 0);
	intInputAge = stoi(inputAge);
	if (intInputAge < 18) {
		std::cout << "You are not old enough to create an account!\n";
		return 0;
	}
	else {
		do {
			std::cout << "Please enter your first name: ";
			std::getline(std::cin >> std::ws, inputFirstName);
			firstNameValidity = checkFirstNameValidity(inputFirstName);
		} while (firstNameValidity == 0);
		do {
			std::cout << "Please enter your second name: ";
			std::getline(std::cin >> std::ws, inputSecondName);
			secondNameValidity = checkSecondNameValidity(inputSecondName);
		} while (secondNameValidity == 0);

		std::cout << "Please enter your postcode: ";
		std::getline(std::cin >> std::ws, inputPostcode);
		for (int i = 0; i < inputPostcode.length(); i++) {
			if (inputPostcode[i] == ' ') {
				inputPostcode.erase(i, 1);
			}
			
		}
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
		age = intInputAge;
		postcode = inputPostcode;
		accountNumber = generateAccountNumber();
		std::cout << "Below is your new account number. Please do not forget this!\n";
		std::cout << accountNumber << '\n';
		return 1;
	}
}

void Account::saveUserDetails(std::string firstName, std::string secondName, int age, std::string postcode,std::string password, std::string accountNumber) {
	std::fstream myFile;
	myFile.open("Accounts.txt", std::ios::app);
	if (myFile.is_open()) {
		myFile << accountNumber << "    " << firstName << "    " << secondName << "    " << age << "    " << postcode << "    " << balancePence << "    " << password << '\n';
		myFile.close();
	}
}

bool Account::login() {
	int posOfAccountDetails;
	int matchingChars;
	uint32_t accountsSearched = 0;
	std::string inputPassword;
	std::string inputAccountNumber;
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
				accountIndex = accountsSearched;
				if (matchingChars != 19) {
					if (accountsSearched == numberOfAccounts) {
						std::cout << "Your account number was not recognised.\n";
						myFile.close();
						return 0;
					}
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

void Account::loadAccount(std::string accountDetails) {
	// password is already stored in memory
	std::string stringBalance;
	Account account;
	accountNumber = accountDetails.substr(0, 19);

	lengthOfFirstName = 0;
	for (int i = 23; accountDetails[i] != ' '; i++) {
		lengthOfFirstName++;
	}
	firstName = accountDetails.substr(23, lengthOfFirstName);

	startPosSecondName = 27 + lengthOfFirstName;
	lengthOfSecondName = 0;
	for (int i = startPosSecondName; accountDetails[i] != ' '; i++) {
		lengthOfSecondName++;
	}
	secondName = accountDetails.substr(startPosSecondName, lengthOfSecondName);

	startPosAge = startPosSecondName + lengthOfSecondName + 4;
	lengthOfAge = 0;
	for (int i = startPosAge; accountDetails[i] != ' '; i++) {
		lengthOfAge++;
	}
	age = stoi(accountDetails.substr(startPosAge, lengthOfAge));

	startPosPostcode = startPosAge + lengthOfAge + 4;
	lengthOfPostcode = 0;
	for (int i = startPosPostcode; accountDetails[i] != ' '; i++) {
		lengthOfPostcode++;
	}
	postcode = accountDetails.substr(startPosPostcode, lengthOfPostcode);

	startPosBalance = startPosPostcode + lengthOfPostcode + 4;
	lengthOfBalance = 0;
	for (int i = startPosBalance; accountDetails[i] != ' '; i++) {
		lengthOfBalance++;
	}
	stringBalance = accountDetails.substr(startPosBalance, lengthOfBalance);
	balancePence = stoi(stringBalance);
}

int Account::accountActions() {
	std::string x;
	balance = formatBalance(balancePence);

	if (firstLogin) {
		std::cout << " _________________\n";
		std::cout << "|     .:==:.      | Account Number: " << accountNumber << '\n';
		std::cout << "|   .*@+--+%*.    |\n";
		std::cout << "|   +%      %*.   | Balance: " << balance << '\n';
		std::cout << "|   **      **.   |\n";
		std::cout << "|   -@-.  .-@-    | First Name: " << firstName << '\n';
		std::cout << "|     -@@@@+      |\n";
		std::cout << "|   -#@@@@@@#=.   | Second Name: " << secondName << '\n';
		std::cout << "|.-@+.      .=@-. |\n";
		std::cout << "|.%:          :@: | Age: " << age << '\n';
		std::cout << "|:@::::::::::::@- |\n";
		std::cout << "|.==============: | Postcode: " << postcode << '\n';
		std::cout << "|_________________|" << '\n' << '\n';
		firstLogin = 0;
	}
	std::cout << "Choose an option:\n";

	do {
		std::cout << "(1) Deposit money.\n";
		std::cout << "(2) Withdraw money.\n";
		std::cout << "(3) Change account details.\n";
		std::cout << "(4) Delete account.\n";
		std::cout << "(5) Log out.\n";
		std::cin >> x;
		if (x != "1" && x != "2" && x != "3" && x != "4" && x != "5") {
			std::cout << "Please choose an option by entering one of the numbers shown within brackets.\n";
		}
	} while (x != "1" && x != "2" && x != "3" && x != "4" && x != "5");
	return stoi(x);
}

bool Account::deleteAccount(std::string deleteConfirmation) {
	Account account;
	if (deleteConfirmation == "DELETE ACCOUNT") {
		std::string line[MAX_ACCOUNTS];//declared as 100 at top of file
		std::string deleteAccount;
		uint32_t numberOfAccounts = account.numberOfAccounts();
		std::fstream myFile;
		myFile.open("Accounts.txt", std::ios::in);
		if (myFile.is_open()) {
			for (int i = 1; i <= numberOfAccounts; i++) {
				getline(myFile, line[i]);
			}
			myFile.close();
		}
		myFile.open("Accounts.txt", std::ios::out);
		if (myFile.is_open()) {
			for (int i = 1; i <= numberOfAccounts; i++) {
				if (i != accountIndex) {
					myFile << line[i] << '\n';
				}
			}
			myFile.close();
		}
		else {
			std::cout << "Failed to open file.";
		}
		return 1;
	}
	else {
		return 0;
	}
}

bool Account::changeDetails() {
	std::string detailToChange;
	std::cout << "Please choose what you would like to change from the options below:\n";
	do {
		std::cout << "(1) First name\n";
		std::cout << "(2) Second name\n";
		std::cout << "(3) Age\n";
		std::cout << "(4) Postcode\n";
		std::cout << "(5) Password\n";
		std::getline(std::cin >> std::ws, detailToChange);
		if (detailToChange != "1" && detailToChange != "2" && detailToChange != "3" && detailToChange != "4" && detailToChange != "5") {
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
			newFirstNameValidity = checkFirstNameValidity(newFirstName);
		} while (newFirstNameValidity == 0);
		tempAccountDetails = accountDetails;
		tempAccountDetails.erase(startPosFirstName, lengthOfFirstName);
		newAccountDetails = tempAccountDetails.insert(startPosFirstName, newFirstName);
		deleteAccount("DELETE ACCOUNT");
		myFile.open("Accounts.txt", std::ios::app);
		if (myFile.is_open()) {
			myFile << newAccountDetails << '\n';
			myFile.close();
			std::cout << "Your first name has been successfully changed.\n";
			return 1;
		}
		else {
			std::cout << "Failed to open file.\n";
			return 0;
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
			newSecondNameValidity = checkSecondNameValidity(newSecondName);
		} while (newSecondNameValidity == 0);
		tempAccountDetails = accountDetails;
		tempAccountDetails.erase(startPosSecondName, lengthOfSecondName);
		newAccountDetails = tempAccountDetails.insert(startPosSecondName, newSecondName);
		deleteAccount("DELETE ACCOUNT");
		myFile.open("Accounts.txt", std::ios::app);
		if (myFile.is_open()) {
			myFile << newAccountDetails << '\n';
			myFile.close();
			std::cout << "Your second name has been successfully changed.\n";
			return 1;
		}
		else {
			std::cout << "Failed to open file.\n";
			return 0;
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
		tempAccountDetails = accountDetails;
		tempAccountDetails.erase(startPosAge, lengthOfAge);
		newAccountDetails = tempAccountDetails.insert(startPosAge, newAge);
		deleteAccount("DELETE ACCOUNT");
		myFile.open("Accounts.txt", std::ios::app);
		if (myFile.is_open()) {
			myFile << newAccountDetails << '\n';
			myFile.close();
			std::cout << "Your age has been successfully changed.\n";
			return 1;
		}
		else {
			std::cout << "Failed to open file.\n";
			return 0;
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
		tempAccountDetails = accountDetails;
		tempAccountDetails.erase(startPosPostcode, lengthOfPostcode);
		newAccountDetails = tempAccountDetails.insert(startPosPostcode, newPostcode);
		deleteAccount("DELETE ACCOUNT");
		myFile.open("Accounts.txt", std::ios::app);
		if (myFile.is_open()) {
			myFile << newAccountDetails << '\n';
			myFile.close();
			std::cout << "Your postcode has been successfully changed.\n";
			return 1;
		}
		else {
			std::cout << "Failed to open file.\n";
			return 0;
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
				passwordValidity = checkPasswordValidity(newPassword1);
			} while (passwordValidity == 0);
			std::cout << "Please confirm your new password: ";
			std::getline(std::cin >> std::ws, newPassword2);
			if (newPassword1 == newPassword2) {
				int startPosPassword = lengthOfAccountDetails - lengthOfPassword;
				tempAccountDetails = accountDetails;
				tempAccountDetails.erase(startPosPassword, lengthOfPassword);
				newAccountDetails = tempAccountDetails.insert(startPosPassword, newPassword1);
				deleteAccount("DELETE ACCOUNT");
				myFile.open("Accounts.txt", std::ios::app);
				if (myFile.is_open()) {
					myFile << newAccountDetails << '\n';
					myFile.close();
					std::cout << "Your password has been successfully changed.\n";
					return 1;
				}
				else {
					std::cout << "Failed to open file.\n";
					return 0;
				}
			}
			else {
				std::cout << "Your passwords do not match.\n";
				return 0;
			}
		} while (newPassword1 != newPassword2);
	}
}

int64_t Account::deposit(int64_t currentBalancePence) {
	std::string deposit;
	int64_t newBalance;
	bool decimal = 0;
	bool validDeposit = 1;

	do {
		std::cout << "Enter the amount you would like to deposit: ";
		std::getline(std::cin >> std::ws, deposit);

		if (isdigit(deposit[0])) {

			for (int i = 0; deposit[i] != '\0'; i++) {
				if (deposit[i] == '.') {
					decimal = 1;
					break;
				}
			}
			if (decimal) {

				int depositPoundsLength = 0;
				int depositPenceLength = 0;
				std::string depositPounds;
				std::string depositPence;

				for (int i = 0; deposit[i] != '.'; i++) {
					depositPoundsLength++;
				}

				for (int i = depositPoundsLength + 1; deposit[i] != '\0'; i++) {
					depositPenceLength++;
				}

				if (depositPenceLength == 2) {
					depositPounds = deposit.substr(0, depositPoundsLength);
					depositPence = deposit.substr(depositPoundsLength + 1);

					int intDepositPence = stoi(depositPence);
					int intDepositPounds = stoi(depositPounds);
					int depositPoundsToPence = intDepositPounds * 100;
					int64_t totalDepositPence = (int64_t)depositPoundsToPence + intDepositPence;

					newBalance = balancePence + totalDepositPence;
					std::cout << "Your money has been deposited.\n";
					return newBalance;

				}
				else {
					std::cout << "Please ensure your pence are entered in the format .XX\n";
					validDeposit = 0;
				}
			}
			else {
				int64_t depositPence = int64_t(stoi(deposit) * 100);

				newBalance = balancePence + depositPence;
				std::cout << "Your money has been deposited.\n";
				return newBalance;
			}
		}
		else {
			std::cout << "Please ensure you enter a number with two digits after the decimal if pence are being deposited.\n";
			validDeposit = 0;
		}
	} while (validDeposit == 0);
	
}

int64_t Account::withdraw(int64_t currentBalancePence) {
	std::string withdraw;
	int64_t newBalance;
	bool decimal = 0;
	bool validWithdraw = 1;

	do {
		std::cout << "Enter the amount you would like to withdraw: ";
		std::getline(std::cin >> std::ws, withdraw);

		if (isdigit(withdraw[0])) {

			for (int i = 0; withdraw[i] != '\0'; i++) {
				if (withdraw[i] == '.') {
					decimal = 1;
					break;
				}
			}
			if (decimal) {

				int withdrawPoundsLength = 0;
				int withdrawPenceLength = 0;
				std::string withdrawPounds;
				std::string withdrawPence;

				for (int i = 0; withdraw[i] != '.'; i++) {
					withdrawPoundsLength++;
				}

				for (int i = withdrawPoundsLength + 1; withdraw[i] != '\0'; i++) {
					withdrawPenceLength++;
				}

				if (withdrawPenceLength == 2) {
					withdrawPounds = withdraw.substr(0, withdrawPoundsLength);
					withdrawPence = withdraw.substr(withdrawPoundsLength + 1);

					int intWithdrawPence = stoi(withdrawPence);
					int intWithdrawPounds = stoi(withdrawPounds);
					int withdrawPoundsToPence = intWithdrawPounds * 100;
					int64_t totalWithdrawPence = (int64_t)withdrawPoundsToPence + intWithdrawPence;

					newBalance = balancePence - totalWithdrawPence;
					if (newBalance >= 0) {
						std::cout << "Your money has been withdrawn.\n";
						return newBalance;
					}
					else {
						std::cout << "You do not have enough money in your account to withdraw this much.\n";
						validWithdraw = 0;
					}

				}
				else {
					std::cout << "Please ensure your pence are entered in the format .XX\n";
					validWithdraw = 0;
				}
			}
			else {
				int64_t depositPence = int64_t(stoi(withdraw) * 100);

				newBalance = balancePence + depositPence;
				std::cout << "Your money has been deposited.\n";
				return newBalance;
			}
		}
		else {
			std::cout << "Please ensure you enter a number with two digits after the decimal if pence are being deposited.\n";
			validWithdraw = 0;
		}
	} while (validWithdraw == 0);
}

std::string Account::formatBalance(int64_t balancePence) {
	std::string penceTens;
	std::string penceUnits;

	std::string strBalance = std::to_string(balancePence);
	int balanceLength = strBalance.length();

	if (balanceLength == 1) {
		penceUnits = strBalance[balanceLength-1];
		strBalance = "0.0" + penceUnits;
	}
	else if (balanceLength == 2) {
		penceTens = strBalance[balanceLength - 2];
		penceUnits = strBalance[balanceLength - 1];
		strBalance = "0." + penceTens + penceUnits;
	}
	else {
		penceTens = strBalance[balanceLength - 2];
		penceUnits = strBalance[balanceLength - 1];
		strBalance.erase(balanceLength - 2, 2);
		strBalance = strBalance + "." + penceTens + penceUnits;
	}

	return strBalance;
}
