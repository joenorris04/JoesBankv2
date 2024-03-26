#pragma once
#include <iostream>

class Account {
public:
	void getUserDetails();
	void login();

private:
	std::string firstName;
	std::string secondName;
	int age;
	std::string postcode;
	std::string password;
	uint32_t accountNumber;

};