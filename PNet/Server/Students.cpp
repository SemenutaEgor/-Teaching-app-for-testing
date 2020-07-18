#include "Students.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>


Students::Students(std::string newname, std::string newpassword, uint32_t newpoints)
{
	name = newname;
	password = newpassword;
	points = newpoints;
}

void Students::NewStudent()
{
	std::string studentName;
	std::string studentPassword;
	std::cout << "Enter name..." << std::endl;
	std::cin >> studentName;
	std::cout << "Enter password..." << std::endl;
	std::cin >> studentPassword;
	name = studentName;
	password = studentPassword;
	points = 0;
}

void Students::SetName(std::string newname)
{
	name = newname;
}

std::string Students::GetName()
{
	return name;
}

void Students::SetPassword(std::string newpassword)
{
	password = newpassword;
}

std::string Students::GetPassword()
{
	return password;;
}

void Students::SetPoints(uint32_t newpoints)
{
	points = newpoints;
}

int Students::GetPoints()
{
	return points;
}

void Students::PrintStudents()
{
	std::cout << "Name: " << name << " Password:" << password << " Points: " << points << std::endl;
}

void Students::MixWord()
{
	std::ifstream MixWord("MixWord.txt");
	if (!MixWord.is_open())
		std::cout << "MixWord.txt not open\n";
	else
	{
		std::vector<std::string> WordArray;
		std::string word;
		while (!MixWord.eof())
		{
			getline(MixWord, word);
			WordArray.push_back(word);
		}

		std::cout << "Next - 1, Exit - 0" << std::endl;
		int com = 1;
		std::string initialWord = "";
		std::string shuffleWord = "";
		std::string enterWord = "";

		while (com)
		{
			initialWord = shuffleWord = WordArray[rand() % 5];
			random_shuffle(shuffleWord.begin(), shuffleWord.end());
			std::cout << shuffleWord << std::endl;
			std::cin >> enterWord;
			if (enterWord == initialWord)
			{
				std::cout << "Yes: +1" << std::endl;
				points += 1;
				std::cout << "Next?" << std::endl;
				std::cin >> com;
			}
			else
			{
				std::cout << "No: 0" << std::endl;
				std::cout << "Next?" << std::endl;
				std::cin >> com;
			}
		}

		std::cout << "You have" << points << " points" << std::endl;
		/*copy(WordArray.begin(), WordArray.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
		std::cout << std::endl;*/
		/*std::getline(MixWord, word);
		std::string str;
		std::cout << "Please enter a  word: "; //ask for input
		std::cin >> str;
		random_shuffle(str.begin(), str.end());
		std::cout << str << std::endl;*/
	}
}