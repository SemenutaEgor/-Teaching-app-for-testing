//Client
#pragma comment (lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <iostream>
#include <string>

SOCKET Connection; //This client's connection ti the server

void ClientThread() {
	//char buffer[256]; //Create buffer to hold messages up to 256 characters
	int bufferlength; //Hold the length of the buffer 
	while (true) {
		recv(Connection, (char*)&bufferlength, sizeof(int), NULL); //receive buffer length
		char * buffer = new char[bufferlength+1]; //Allocate buffer
		buffer[bufferlength] = '\0'; //Set last character of buffer to be null terminator so we arent printing info we dont want
		recv(Connection, buffer, bufferlength, NULL); //Receive message from server
		std::cout << buffer << std::endl; //print out buffer
		delete[] buffer; //Deallocate buffer
	}
}

int main() {

	//WinSock Startup
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0) { //If WSAStartup returns anything ither than 0, than that means an error has occured in the WinSock Startup
		MessageBoxA(NULL, "WinSock startup failed", "Error", MB_OK | MB_ICONERROR); 
		exit(1);
	}

	SOCKADDR_IN addr; //Address to be binded to our Connection socket
	int sizeofaddr = sizeof(addr); //Need sizeofaddr for the connect function
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Address = localhoct (this pc)
	addr.sin_port = htons(1111); //Port =  1111
	addr.sin_family = AF_INET; //IPv4 Socket

	Connection = socket(AF_INET, SOCK_STREAM, NULL); //Set connection socket
	if (connect(Connection, (SOCKADDR*)&addr, sizeofaddr) != 0) { //If we are unable to connect...
		MessageBoxA(NULL, "Failed to connect", "Error", MB_OK | MB_ICONERROR);
		return 0; //Failed to connect
	}
	std::cout << "Connected!" << std::endl;
	/*char MOID[256];
	recv(Connection, MOID, sizeof(MOID), NULL); //Recieve Message of the day  buffer into MOID array 
	std::cout << "MOID:" << MOID << std::endl;*/
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientThread, NULL, NULL, NULL); //Create the client thread

	//char buffer[256]; //256 char buffer to send message 
	std::string buffer; //string bufffer to send message
	while (true) {
		std::getline(std::cin, buffer); //Get line if user preses enter and fill the buffer
		int bufferlength = buffer.size();
		send(Connection, (char*)&bufferlength, sizeof(int), NULL); //Send length of buffer 
		send(Connection, buffer.c_str(), bufferlength, NULL); //Send buffer
		Sleep(10);
	}

	system("pause");

	return 0;
}
