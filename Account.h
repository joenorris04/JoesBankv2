#pragma once
#include <iostream>

class Account {
public:
	void getUserDetails();
	void login();
	bool checkFirstNameValidity(std::string inputName);
	bool checkSecondNameValidity(std::string inputName);
	bool checkPasswordValidity(std::string inputPassword);

private:
	std::string firstName;
	std::string secondName;
	int age;
	std::string postcode;
	std::string password;
	uint32_t accountNumber;

};