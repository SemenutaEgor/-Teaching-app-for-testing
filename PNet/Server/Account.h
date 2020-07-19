#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

struct Account
{
	std::string username;
	std::string password;
	int points;

	Account(std::string username, std::string password, int points)
		: username(username), password(password), points(points) {}
};

void RecordData();
void ReadData();

bool IsAccountValid(std::string username, std::string userpassword);
bool CreateAccount(std::string username, std::string userpassword);
bool AddPoints(std::string username, int userpoints);
void PrintAccounts();

std::string CaesarCoder(std::string originalPassword);
std::string CaesarDecoder(std::string encryptedPassword);

static std::vector<Account> accountsVector = {};
/* 
{
	{"pindrought", "badpassword", 0},
	{"egor", "betterpassword9681", 0},
};*/