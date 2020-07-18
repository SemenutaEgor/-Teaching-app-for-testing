#pragma once
#include <string>

class Students
{
public:
	Students() { name = "Name"; password = "qwerty", points = 0; }
	Students(std::string newname, std::string password, uint32_t newpoints);

	void NewStudent();

	void SetName(std::string newname);
	std::string GetName();

	void SetPassword(std::string newpassword);
	std::string GetPassword();

	void SetPoints(uint32_t newpoints);
	int GetPoints();

	void PrintStudents();

	void MixWord();
private:
	std::string name;
	std::string password;
	uint32_t points;
};