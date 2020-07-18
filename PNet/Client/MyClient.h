#pragma once
#include <PNet/IncludeMe.h>
#include "Tasks.h"

class MyClient : public Client
{
private:
	bool ProcessPacket(std::shared_ptr<Packet> packet) override;
	void OnConnect() override;
	void OnDisconnect(std::string reason) override;
	
	//void OnConnectFail() override;
	//void OnDisconnect(std::string reason) override;
public:
	void SendAccountCredentials(std::string username, std::string userpassword);
	void SendNewAccount(std::string username, std::string userpassword);
	void SendPoints(std::string username, int points);
};