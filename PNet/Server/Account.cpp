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

	accountsVector.push_back({ newusername, newuserpassword });
	return true;

}

void PrintAccounts()
{
	for (int i = 0; i < accountsVector.size(); i++)
	{
		std::cout << "Name: " << accountsVector[i].username << std::endl;
		std::cout << "Password: " << accountsVector[i].password << std::endl;
	}
}
