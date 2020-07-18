#include "MyServer.h"
#include "Students.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

void MyServer::OnConnect(TCPConnection & newConnection)
{
	std::cout << newConnection.ToString() << " - New connection accepted." << std::endl;

	std::shared_ptr<Packet> welcomeMessagePacket = std::make_shared<Packet>(PacketType::PT_ChatMessage);
	*welcomeMessagePacket << std::string("Welcome!");
	newConnection.pm_outgoing.Append(welcomeMessagePacket);

	std::shared_ptr<Packet> newUserMessagePacket = std::make_shared<Packet>(PacketType::PT_ChatMessage);
	*newUserMessagePacket << std::string("New user connected!");
	for (auto & connection : connections)
	{
		if (&connection == &newConnection)
			continue;

		connection.pm_outgoing.Append(newUserMessagePacket);
	}
}

void MyServer::OnDisconnect(TCPConnection & lostConnection, std::string reason)
{
	std::cout << "[" << reason << "] Connection lost: " << lostConnection.ToString() << "." << std::endl;

	std::shared_ptr<Packet> connectionLostPacket = std::make_shared<Packet>(PacketType::PT_ChatMessage);
	*connectionLostPacket << std::string("A user disconnected!");
	for (auto & connection : connections)
	{
		if (&connection == &lostConnection)
			continue;

		connection.pm_outgoing.Append(connectionLostPacket);
	}
}

bool MyServer::ProcessPacket(std::shared_ptr<Packet> packet)
{
	switch (packet->GetPacketType())
	{
	case PacketType::PT_ChatMessage:
	{
		std::string chatmessage;
		*packet >> chatmessage;
		std::cout << "Message: " << chatmessage << std::endl;
		break;
	}
	case PacketType::PT_Student:
	{
		std::string nameString;
		*packet >> nameString;
		//std::cout << "Name: " << nameString << std::endl;

		std::string passwordString;
		*packet >> passwordString;
		//std::cout << "Password: " << passwordString << std::endl;

		std::string pointsString;
		*packet >> pointsString;
		//std::cout << "Points: " << pointsString << std::endl;

		uint32_t pointsInt = atoi(pointsString.c_str());
		Students student(nameString, passwordString, pointsInt);
		student.PrintStudents();

		std::string resultString = nameString + " " + pointsString;
		std::ofstream save_result;                    
		save_result.open("Results.txt", std::ios::app);  
		save_result << resultString << std::endl;  
		//save_result << \n;
		save_result.close();
		break;
	}
	case PacketType::PT_IntegerArray:
	{
		uint32_t arraySize = 0;
		*packet >> arraySize;
		std::cout << "Array Size: " << arraySize << std::endl;
		for (uint32_t i = 0; i < arraySize; i++)
		{
			uint32_t element = 0;
			*packet >> element;
			std::cout << "Element - [" << i << "] - " << element << std::endl;
		}
		break;
	}
	default:
		std::cout << "Unrecognized packet type: " << packet->GetPacketType() << std::endl;
		return false;
	}

	return true;
}

