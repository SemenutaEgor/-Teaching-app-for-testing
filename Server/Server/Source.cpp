//Server
#pragma comment(lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <iostream>

int main() {

	//WinSock Startup
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0) { //If WSAStartup returns anything ither than 0, than that means an error has occured in the WinSock Startup
		MessageBoxA(NULL, "WinSock startup failed", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	SOCKADDR_IN addr; //Address tha the will bind our listening socket to
	int addrlen = sizeof(addr); //lenght of the address (required for accept call)
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Broadcast locally
	addr.sin_port = htons(1111); //Port
	addr.sin_family = AF_INET; //IPv4 Socket

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL); //Create socket to listen for new connections
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr)); //Bind the address to the socket
	listen(sListen, SOMAXCONN); //Places sListen socket in a state in which is in listening for an incoming connection. Note: SOMAXCONN = Socket Outstanding Max Connections

	SOCKET newConnection; // Socket to hold the client's connection
	newConnection = accept(sListen, (SOCKADDR*)&addr, &addrlen); //Accept a new connection
	if (newConnection == 0) { //If accepting the client's connection failed
		std::cout << "Failed to accept the client's connection" << std::endl;
	}
	else { //If client connection properly accepted
		std::cout << "Client connected!" << std::endl;
		char MOID[256] = "Welcome! This is a Message of the Day."; //Create buffer with message of the day
		send(newConnection, MOID, sizeof(MOID), NULL); //Send MOID buffer
	}
	system("pause");
	return 0;
}