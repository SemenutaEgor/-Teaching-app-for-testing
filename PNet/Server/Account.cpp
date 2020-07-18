#include "Account.h"

bool IsAccountValid(std::string username, std::string userpassword)
{
	for (auto & acct : accountsVector)
	{
		if (acct.username == username)
		{
			if (acct.password == userpassword)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}

bool CreateAccount(std::string newusername, std::string newuserpassword)
{
	for (auto & acct : accountsVector)
	{
		if (acct.username == newusername)
		{
			return false;
		}
	}

	accountsVector.push_back({ newusername, newuserpassword, 0 });
	return true;

}

bool AddPoints(std::string username, int userpoints)
{
	for (auto & acct : accountsVector)
	{
		if (acct.username == username)
		{
			acct.points += userpoints;
			return true;
		}
	}
	return false;
}

void PrintAccounts()
{
	std::cout << "Current status of accounts:" << std::endl;
	for (auto & acct : accountsVector)
	{
		std::cout << "Name: " << acct.username << std::endl;
		std::cout << "Password: " << acct.password << std::endl;
		std::cout << "Points: " << acct.points << std::endl;
	}
}
