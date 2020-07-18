#pragma once
#include <string>
#include <vector>
#include <iostream>

struct Account
{
	std::string username;
	std::string password;
};

bool IsAccountValid(std::string username, std::string userpassword);
bool CreateAccount(std::string username, std::string userpassword);
void PrintAccounts();

static std::vector<Account> accountsVector =
{
	{"pindrought", "badpassword"},
	{"egor", "betterpassword9681"},
};