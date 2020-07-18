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
		else
		{
			accountsVector.push_back({ newusername, newuserpassword });
			return true;
		}
	}

}
