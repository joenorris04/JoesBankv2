#pragma once
#include <iostream>

class Account {
public:
	std::string firstName;
	std::string secondName;
	int age;
	std::string postcode;
	std::string password;
	std::string accountNumber;
	void getUserDetails();
	std::string generateAccountNumber();
	void login();
	bool checkFirstNameValidity(std::string inputName);
	bool checkSecondNameValidity(std::string inputName);
	bool checkPasswordValidity(std::string inputPassword);
	void saveUserDetails(std::string firstName, std::string secondName, int age, std::string postcode, std::string password, std::string accountNumber);

private:

};