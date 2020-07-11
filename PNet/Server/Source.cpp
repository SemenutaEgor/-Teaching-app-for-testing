//Server Code
#include <PNet\IncludeMe.h>
#include <iostream>

using namespace PNet;

int main() 
{ 
	if (Network::Initialize())
	{
		std::cout << "Winsock api successfully initialized." << std::endl;

		IPEndpoint test("192.168.0.257", 8080);
		if (test.GetIPVersion() == IPVersion::IPv4)
		{
			std::cout << "Hostmane: " << test.GetHostName() << std::endl;
			std::cout << "IP: " << test.GetIPString() << std::endl;
			std::cout << "Port: " << test.GetPort() << std::endl;
			std::cout << "IP Bytes... " << std::endl;
			for (auto & digit : test.GetIPBytes())
			{
				std::cout << (int)digit << std::endl;
			}
		}
		else
		{
			std::cerr << "This is not an ipv4 address." << std::endl;
		}

		Socket socket;
		if (socket.Create() == PResult::P_Success)
		{
			std::cout << "Socket successfully created." << std::endl;
			socket.Close();
		}
		else
		{
			std::cerr << "Socket failed to create." << std::endl;

		}
 	}
	Network::Shutdown();
	return 0;
}