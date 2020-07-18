#include "MyServer.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>


/*void MyServer::SendData(TCPConnection & newConnection)
{
	std::shared_ptr<Packet> dataPacket = std::make_shared<Packet>(PacketType::PT_Data);
	*dataPacket << std::string("Welcome!");
	newConnection.pm_outgoing.Append(dataPacket); 
}*/

void MyServer::OnConnect(TCPConnection & newConnection)
{
	/*std::cout << newConnection.ToString() << " - New connection accepted." << std::endl;

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
	}*/
	std::cout << newConnection.ToString() << " - New connection established... Awaiting for account credentials..." << std::endl;
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

//bool MyServer::ProcessPacket(std::shared_ptr<Packet> packet)
bool MyServer::ProcessPacket(int connectionIndex, std::shared_ptr<Packet> packet)
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
	case PacketType::PT_ClientConnect:
	{
		std::string username;
		std::string userpassword;
		*packet >> username >> userpassword;
		std::cout << "User tried to connect with the following credentials [" << username << "] / [" << userpassword << "]" << std::endl;
		if (IsAccountValid(username, userpassword))
		{
			std::cout << "Account credentials are valid!" << std::endl;
			std::shared_ptr<Packet> accountPacket = std::make_shared<Packet>(PacketType::PT_ChatMessage);
			*accountPacket << std::string("Logged in.");
			connections[connectionIndex].pm_outgoing.Append(accountPacket);
			return true;
		}
		else
		{
			std::cout << "Account credentials are bad! Aborting connection!" << std::endl;
			connections[connectionIndex].shutdownMode = true; //By setting shutdownmode to true, this connection will close once all outgoing packets are sent. No more incoming packets will be processed for this connection.
			std::shared_ptr<Packet> badAccountDataPacket = std::make_shared<Packet>(PacketType::PT_BadAccountData);
			connections[connectionIndex].pm_outgoing.Append(badAccountDataPacket);
			return true;
		}
		break;
	}
	case PacketType::PT_NewAccount:
	{
		std::string username;
		std::string userpassword;
		*packet >> username >> userpassword;
		std::cout << "User tried to create account with the following credentials [" << username << "] / [" << userpassword << "]" << std::endl;
		if (CreateAccount(username, userpassword))
		{
			std::cout << "Account created!" << std::endl;
			std::shared_ptr<Packet> createdPacket = std::make_shared<Packet>(PacketType::PT_ChatMessage);
			*createdPacket << std::string("Account created");
			connections[connectionIndex].pm_outgoing.Append(createdPacket);
			PrintAccounts();
			return true;
		}
		else
		{
			std::cout << "This name already exists! Aborting connection!" << std::endl;
			connections[connectionIndex].shutdownMode = true; //By setting shutdownmode to true, this connection will close once all outgoing packets are sent. No more incoming packets will be processed for this connection.
			std::shared_ptr<Packet> badAccountDataPacket = std::make_shared<Packet>(PacketType::PT_BadAccountData);
			connections[connectionIndex].pm_outgoing.Append(badAccountDataPacket);
			return true;
		}
		break;
	}
	case PacketType::PT_AddPoints:
	{
		std::string username;
		std::string userpointsString;
		*packet >> username >> userpointsString;
		int userpoints = std::stoi(userpointsString);
		if (AddPoints(username, userpoints))
		{
			std::cout << "Account " << username << " get " << userpoints << " points" << std::endl;
			std::shared_ptr<Packet> pointsPacket = std::make_shared<Packet>(PacketType::PT_ChatMessage);
			*pointsPacket << std::string(userpointsString + "points added.");
			connections[connectionIndex].pm_outgoing.Append(pointsPacket);
			PrintAccounts();
			return true;
		}
		else
		{
			std::cout << "Some error, no points added" << std::endl;
			connections[connectionIndex].shutdownMode = true; //By setting shutdownmode to true, this connection will close once all outgoing packets are sent. No more incoming packets will be processed for this connection.
			std::shared_ptr<Packet> badAccountDataPacket = std::make_shared<Packet>(PacketType::PT_BadAccountData);
			connections[connectionIndex].pm_outgoing.Append(badAccountDataPacket);
			return true;
		}
		break;
	}
	default:
		std::cout << "Unrecognized packet type: " << packet->GetPacketType() << std::endl;
		return false;
	}

	return true;
}

