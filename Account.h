#pragma once
#include <iostream>

class Account {
public:
	std::string firstName;
	std::string secondName;
	int age; // uninitialised error
	std::string postcode;
	std::string password;
	std::string accountDetails;
	int lengthOfAccountDetails;
	int lengthOfPassword = 0;
	std::string accountNumber;
	int64_t balance = 0;
	uint32_t accountIndex;
	uint32_t numberOfAccounts();
	bool getUserDetails();
	std::string generateAccountNumber();
	bool login();
	bool checkFirstNameValidity(std::string inputName);
	bool checkSecondNameValidity(std::string inputName);
	bool checkPasswordValidity(std::string inputPassword);
	void saveUserDetails(std::string firstName, std::string secondName, int age, std::string postcode, std::string password, std::string accountNumber);
	bool checkAccountNumberValidity(std::string inputAccountNumber);
	void loadAccount(std::string accountDetails);
	int accountActions();
	bool deleteAccount();
};

