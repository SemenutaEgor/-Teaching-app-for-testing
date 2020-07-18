#pragma once
#include <PNet/IncludeMe.h>
#include"Students.h"
#include "Account.h"

using namespace std;

class MyServer : public Server
{
public:
	//void SendData(TCPConnection & newConnection);
private:
	void OnConnect(TCPConnection & newConnection) override;
	void OnDisconnect(TCPConnection & lostConnection, std::string reason) override;
	//bool ProcessPacket(std::shared_ptr<Packet> packet) override;
	bool ProcessPacket(int connectionIndex, std::shared_ptr<Packet> packet) override;
};