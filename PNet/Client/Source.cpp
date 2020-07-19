//Client Code
#include "MyClient.h"
#include <iostream>
#include <thread>
#include <conio.h>

MyClient client;

std::string HidePassword()
{
	std::vector<char> vectorPassword;
	char c;

	std::cout << "Enter password: " << std::endl;
	while ((c = _getch()) != '\r')
	{
		vectorPassword.push_back(c);
		_putch('*');
	}

	std::string stringPassword(vectorPassword.begin(), vectorPassword.end());
	return stringPassword;
}

void loading()
{
	while (client.IsConnected())
	{
		client.Frame();
	}
}

int main()
{
	if (Network::Initialize())
	{
		if (client.Connect(IPEndpoint("::1", 6112)))
		{
			std::thread thr(loading);
			int com = -1;
			std::string username = "";
			std::string userpassword = "";
			while (com != 0)
			{
				std::cout << "\nSign in - 1, Sign up - 2, MixWord - 3, Arithmetic - 4, Exit - 0" << std::endl;
				std::cin >> com;
				switch (com)
				{
				case 1:
				{
					std::cout << "Enter username:" << std::endl;
					//std::string username;
					std::cin >> username;
					//std::cout << "Enter password:" << std::endl;
					//std::string userpassword;
					//std::cin >> userpassword;
					userpassword = HidePassword();
					client.SendAccountCredentials(username, userpassword);
					//client.Frame();
					break;
				}
				case 2:
				{
					std::cout << "Enter username:" << std::endl;
					//std::string username;
					std::cin >> username;
					//std::cout << "Enter password:" << std::endl;
					//std::string userpassword;
					//std::cin >> userpassword;
					userpassword = HidePassword();
					client.SendNewAccount(username, userpassword);
					//client.Frame();
					break;
				}
				case 3:
				{
					std::cout << "Reconstruct the mixed word." << std::endl;
					int points = 0;
					points = MixWord();
					client.SendPoints(username, points);
					break;
				}
				case 4:
				{
					std::cout << "Ñalculated the expression." << std::endl;
					int points = 0;
					points = Arithmetic();
					client.SendPoints(username, points);
					break;
				}
				case 0:
					break;
				}
			}
			Network::Shutdown();
			thr.join();
		}
		//Network::Shutdown();
		system("pause");
		return 0;
	}
}
