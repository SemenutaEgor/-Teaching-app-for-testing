#pragma once
#include <string>
#include <vector>
#include <iostream>

struct Account
{
	std::string username;
	std::string password;
	int points;
};

bool IsAccountValid(std::string username, std::string userpassword);
bool CreateAccount(std::string username, std::string userpassword);
bool AddPoints(std::string username, int userpoints);
void PrintAccounts();

static std::vector<Account> accountsVector =
{
	{"pindrought", "badpassword", 0},
	{"egor", "betterpassword9681", 0},
};