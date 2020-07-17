//Client Code
#include "MyClient.h"
#include <iostream>
#include "Students.h"

int main()
{
	//Students student("student", 0);
	//student.MixWord();

	if (Network::Initialize())
	{
		MyClient client;
		if (client.Connect(IPEndpoint("::1", 6112)))
		{
			int com = 1;
			while (com)
			{
				client.Frame();
				std::string studentName;
				std::cout << "Enter name..." << std::endl;
				std::cin >> studentName;
				Students student(studentName, 0);
				student.MixWord();
				std::string pointsString = std::to_string(student.GetPoints());
				client.SendStudent(student.GetName(), pointsString);
				client.Frame();
				std::cout << "Again - 1, Exit - 0" << std::endl;
				std::cin >> com;
			}
			/*while (client.IsConnected())
			{
				client.Frame();
				client.SendName(student.GetName());
				client.SendPoints(pointsString);
				//system("pause");
			}*/
		}
	}
	/*if (Network::Initialize())
	{
		MyClient client;
		if (client.Connect(IPEndpoint("::1", 6112)))
		{
			while (client.IsConnected())
			{
				client.Frame();
				client.SendString("myString");
			}
		}
	} */
	Network::Shutdown();
	system("pause");
	return 0;
}

/*int main()
{
	int a = 0;
	std::string str = "";

	std::cout << "Enter name:" << std::endl;
	std::cin >> str;
	std::cout << "Enter points:" << std::endl;
	std::cin >> a;

	Students N(str, a);
	N.PrintStudents();
}*/