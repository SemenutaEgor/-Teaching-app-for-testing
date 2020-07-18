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

