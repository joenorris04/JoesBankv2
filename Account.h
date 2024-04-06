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
	int startPosFirstName = 23;
	int lengthOfFirstName;
	int startPosSecondName;
	int lengthOfSecondName;
	int startPosAge;
	int lengthOfAge;
	int startPosPostcode;
	int lengthOfPostcode;
	int startPosBalance;
	int lengthOfBalance;
	std::string accountNumber;
	int64_t balancePence = 0;
	std::string balance;
	uint32_t accountIndex;
	uint32_t numberOfAccounts();
	bool firstLogin = 1;
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
	bool deleteAccount(std::string deleteConfirmation);
	bool changeDetails();
	int64_t deposit(int64_t currentBalancePence);
	int64_t withdraw(int64_t currentBalancePence);
	std::string formatBalance(int64_t balancePence);

private:
	
};

