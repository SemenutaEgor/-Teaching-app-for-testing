#include "MyClient.h"
#include <iostream>

void MyClient::SendAccountCredentials(std::string username, std::string userpassword)
{
	std::shared_ptr<Packet> accountPacket = std::make_shared<Packet>(PacketType::PT_ClientConnect);
	*accountPacket << username << userpassword;
	connection.pm_outgoing.Append(accountPacket);
}

void MyClient::SendNewAccount(std::string username, std::string userpassword)
{
	std::shared_ptr<Packet> accountPacket = std::make_shared<Packet>(PacketType::PT_NewAccount);
	*accountPacket << username << userpassword;
	connection.pm_outgoing.Append(accountPacket);
}

void MyClient::SendPoints(std::string username, int points)
{
	std::shared_ptr<Packet> pointsPacket = std::make_shared<Packet>(PacketType::PT_AddPoints);
	std::string pointsString = std::to_string(points);
	*pointsPacket << username << pointsString;
	connection.pm_outgoing.Append(pointsPacket);
}

bool MyClient::ProcessPacket(std::shared_ptr<Packet> packet)
{
	switch (packet->GetPacketType())
	{
	case PacketType::PT_ChatMessage:
	{
		std::string chatmessage;
		*packet >> chatmessage;
		std::cout << "Chat Message: " << chatmessage << std::endl;
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
			std::cout << "Element[" << i << "] - " << element << std::endl;
		}
		break;
	}
	case PacketType::PT_BadAccountData:
		std::cout << "Bad account data. Connection refused." << std::endl;
		return true;
	default:
		std::cout << "Unrecognized packet type: " << packet->GetPacketType() << std::endl;
		return false;
	}

	return true;
}

void MyClient::OnConnect()
{
	std::cout << "Successfully connected to the server!" << std::endl;

	std::cout << "Connection with server established." << std::endl;

	std::shared_ptr<Packet> helloPacket = std::make_shared<Packet>(PacketType::PT_ChatMessage);
	*helloPacket << std::string("Hello from the client!");
	connection.pm_outgoing.Append(helloPacket);
}

void MyClient::OnDisconnect(std::string reason)
{
	std::cout << "Lost connection to server! Reason: " << reason << std::endl;
}



