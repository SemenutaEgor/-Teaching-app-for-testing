//Server Code
#include <PNet\IncludeMe.h>
#include <iostream>

using namespace PNet;

int main() 
{
	if (Network::Initialize())
	{
		std::cout << "Winsock api successfully initialized." << std::endl;
 	}
	Network::Shutdown();
	return 0;
}