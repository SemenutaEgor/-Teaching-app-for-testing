#pragma once
#include <string>

class Students
{
public:
	Students() { name = ""; points = 0; }
	Students(std::string newname, uint32_t newpoints);

	void SetName(std::string newname);
	std::string GetName();

	void SetPoints(uint32_t newpoints);
	int GetPoints();

	void PrintStudents();

	void MixWord();
private:
	std::string name;
	uint32_t points;
};