#pragma once
#include <PNet/IncludeMe.h>
#include "Students.h"

class MyClient : public Client
{
private:
	bool ProcessPacket(std::shared_ptr<Packet> packet) override;
	void OnConnect() override;
	void OnDisconnect(std::string reason) override;
	
	//void OnConnectFail() override;
	//void OnDisconnect(std::string reason) override;
public:
	void SendName(std::string myString);
	void SendStudent(std::string name, std::string passwordString, std::string pointsString);
	void SendAccountCredentials(std::string username, std::string userpassword);
	void SendNewAccount(std::string username, std::string userpassword);
};