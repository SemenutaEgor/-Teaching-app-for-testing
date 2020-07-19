#include "Tasks.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>

int MixWord()
{
	int mixPoints = 0;
	std::ifstream MixWord("MixWord.txt");
	if (!MixWord.is_open())
		std::cout << "MixWord.txt not open\n";
	else
	{
		std::vector<std::string> WordArray;
		std::string word;
		int size = 0;
		while (!MixWord.eof())
		{
			getline(MixWord, word);
			WordArray.push_back(word);
			size += 1;
		}

		std::cout << "Next - 1, Exit - 0" << std::endl;
		int com = 1;
		std::string initialWord = "";
		std::string shuffleWord = "";
		std::string enterWord = "";

		while (com)
		{
			initialWord = shuffleWord = WordArray[rand() % size];
			random_shuffle(shuffleWord.begin(), shuffleWord.end());
			std::cout << shuffleWord << std::endl;
			std::cin >> enterWord;
			if (enterWord == initialWord)
			{
				std::cout << "Yes: +1" << std::endl;
				mixPoints += 1;
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

		std::cout << "You get " << mixPoints << " points" << std::endl;
	}
	return mixPoints;
}

int Arithmetic()
{
	int arPoints = 0;
	int randNumber1 = 0;
	int randNumber2 = 0;
	int realResult = 0;
	int enterResult = 0;
	int var = 0;
	int com = 1;
	while (com)
	{
		var = rand() % 3;
		switch (var)
		{
		case 0:
			randNumber1 = rand() % 10;
			randNumber2 = rand() % 10;
			realResult = randNumber1 + randNumber2;
			std::cout << "\n" << randNumber1 << " + " << randNumber2 << " = ";
			std::cin >> enterResult;
			if (enterResult == realResult)
			{
				std::cout << " Yes: +1 " << std::endl;
				arPoints += 1;
				std::cout << " Next? " << std::endl;
				std::cin >> com;
			}
			else
			{
				std::cout << " No: 0 " << std::endl;
				std::cout << " Next? " << std::endl;
				std::cin >> com;
			}
			break;
		case 1:
			randNumber1 = rand() % 10;
			randNumber2 = rand() % 10;
			realResult = randNumber1 - randNumber2;
			std::cout << "\n" << randNumber1 << " - " << randNumber2 << " = ";
			std::cin >> enterResult;
			if (enterResult == realResult)
			{
				std::cout << " Yes: +1 " << std::endl;
				arPoints += 1;
				std::cout << " Next? " << std::endl;
				std::cin >> com;
			}
			else
			{
				std::cout << " No: 0 " << std::endl;
				std::cout << " Next? " << std::endl;
				std::cin >> com;
			}
			break;
		case 2:
			randNumber1 = rand() % 10;
			randNumber2 = rand() % 10;
			realResult = randNumber1 * randNumber2;
			std::cout << "\n" << randNumber1 << " * " << randNumber2 << " = ";
			std::cin >> enterResult;
			if (enterResult == realResult)
			{
				std::cout << " Yes: +1 " << std::endl;
				arPoints += 1;
				std::cout << " Next? " << std::endl;
				std::cin >> com;
			}
			else
			{
				std::cout << " No: 0 " << std::endl;
				std::cout << " Next? " << std::endl;
				std::cin >> com;
			}
			break;
		}
	}
	std::cout << "You get " << arPoints << " points" << std::endl;
	return arPoints;
}

