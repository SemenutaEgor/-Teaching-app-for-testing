#include "MyServer.h"
#include <iostream>

int main()
{
	//ReadData();
	if (Network::Initialize())
	{
		MyServer server;
		if (server.Initialize(IPEndpoint("::", 6112)))
		{
			while (true)
			{
				server.Frame();
			}
		}
		//RecordData();
	}
	Network::Shutdown();
	system("pause");
	return 0;
}