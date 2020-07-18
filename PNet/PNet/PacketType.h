#pragma once
#include <stdint.h>

namespace PNet
{
	enum PacketType : uint16_t
	{
		PT_Invalid,
		PT_ChatMessage,
		PT_IntegerArray,
		PT_ClientConnect, //Sent from client to server to try to connect
		PT_BadAccountData, //Sent from server to client when bad account data has been sent
		PT_NewAccount,
		PT_AddPoints
	};
}