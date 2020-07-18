#include "MyClient.h"
#include "Students.h"
#include <iostream>

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
	case PacketType::PT_Student:
	{
		std::string name;
		*packet >> name;
		std::cout << "Name: " << name << std::endl;

		std::string passwordString;
		*packet >> passwordString;
		std::cout << "Password: " << passwordString << std::endl;

		std::string pointsString;
		*packet >> pointsString;
		std::cout << "Points: " << pointsString << std::endl;
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
	default:
		std::cout << "Unrecognized packet type: " << packet->GetPacketType() << std::endl;
		return false;
	}

	return true;
}

void MyClient::OnConnect()
{
	std::cout << "Successfully connected to the server!" << std::endl;

	std::shared_ptr<Packet> helloPacket = std::make_shared<Packet>(PacketType::PT_ChatMessage);
	*helloPacket << std::string("Hello from the client!");
	connection.pm_outgoing.Append(helloPacket);
}

void MyClient::SendName(std::string myString)
{
	std::shared_ptr<Packet> namePacket = std::make_shared<Packet>(PacketType::PT_ChatMessage);
	*namePacket << myString;
	connection.pm_outgoing.Append(namePacket);
}

void MyClient::SendStudent(std::string name, std::string passwordString, std::string pointsString)
{
	std::shared_ptr<Packet> pointsPacket = std::make_shared<Packet>(PacketType::PT_Student);
	*pointsPacket << name;
	*pointsPacket << passwordString;
	*pointsPacket << pointsString;
	connection.pm_outgoing.Append(pointsPacket);
}

