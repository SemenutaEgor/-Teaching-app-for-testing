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

std::string CaesarCoder(std::string originalPassword)
{
	for (int i = 0; i < originalPassword.length(); i++) {
		if (originalPassword[i] == '9')
			originalPassword[i] = '0';
		else

			if (originalPassword[i] == 'Z') 
				originalPassword[i] = 'A';
			else

				if (originalPassword[i] == 'z')
					originalPassword[i] = 'a';
				else 
					originalPassword[i]++;
	}
	return originalPassword;
}

std::string CaesarDecoder(std::string encryptedPassword)
{
	for (int i = 0; i < encryptedPassword.length(); i++) {
		if (encryptedPassword[i] == '0')
			encryptedPassword[i] = '9';
		else

			if (encryptedPassword[i] == 'A')
				encryptedPassword[i] = 'Z';
			else

				if (encryptedPassword[i] == 'a')
					encryptedPassword[i] = 'z';
				else
					encryptedPassword[i]--;
	}
	return encryptedPassword;
}

void RecordData()
{
	std::ofstream record("AccountData.txt", std::ios::out | std::ios::trunc);
	if (!record.is_open())
		std::cout << "AccountData not open\n";
	else
	{
		time_t seconds = time(NULL);
		tm* timeinfo = localtime(&seconds);
		record << asctime(timeinfo);
		for (auto & acct : accountsVector)
		{
			std::string encryptedPassword = CaesarCoder(acct.password);
			record << acct.username << " " << encryptedPassword << " " << acct.points << std::endl;
		}
		record.close();
	}
}

void ReadData()
{
	std::ifstream read("AccountData.txt", std::ios::app);
	std::string username;
	std::string password;
	std::string encryptedPassword;
	std::string dayOfWeek;
	std::string month;
	std::string day;
	std::string time;
	std::string year;
	int points;
	if (!read.is_open())
		std::cout << "AccountData.txt not open\n";
	else
	{
		read >> dayOfWeek >> month >> day >> time >> year;
		std::cout << "Last record: " << dayOfWeek << " " << month << " " << day << " " << time << " " << year << " " << std::endl;
		while (read >> username >> encryptedPassword >> points)
		{
			password = CaesarDecoder(encryptedPassword);
			accountsVector.push_back(Account(username, password, points));
		}
		read.close();
	}
}

