#include "MyServer.h"
#include <iostream>

int main()
{
	setlocale(LC_ALL, "Russian");
	if (Network::Initialize())
	{
		PrintAccounts();
		MyServer server;
		if (server.Initialize(IPEndpoint("::", 6112)))
		{
			while (true)
			{
				server.Frame();
			}
		}
	}
	Network::Shutdown();
	system("pause");
	return 0;
}