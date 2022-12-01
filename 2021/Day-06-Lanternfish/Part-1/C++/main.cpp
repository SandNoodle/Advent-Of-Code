#include <iostream>
#include <fstream>

#include <numeric>
#include <algorithm>

#include <vector>
#include <string>

bool GetFishData(const char* file, std::vector<int> &fishVector)
{
	std::ifstream inputFile(file);
	if(!inputFile.is_open()) return false;

	std::string line;
	while(std::getline(inputFile, line, ','))
	{
		int value = std::atoi(line.c_str());
		fishVector.at(value) += 1;
	}

	return true;
}

void NextDay(std::vector<int> &fishVector)
{
	std::vector<int> backVector(9);
	backVector.at(6) += fishVector.at(0);
	backVector.at(8) += fishVector.at(0);

	for(int i = 1; i < 9; ++i)
	{
		backVector.at(i - 1) += fishVector.at(i);
	}

	fishVector = backVector;
}

int GetFishCount(const std::vector<int> &fishVector)
{
	int fishCount = 0;

	for(int i = 0; i < 9; ++i)
	{
		fishCount += fishVector.at(i);
	}

	return fishCount;
}

int main(void)
{
	std::vector<int> fishVector(9);
	GetFishData("../../Data/lanternfish-data.txt", fishVector);


	int numberOfDays = 80;
	for(int i = 0; i < numberOfDays; ++i)
	{
		NextDay(fishVector);
	}

	std::cout << "Lanternfish count after " <<  numberOfDays << " is " << GetFishCount(fishVector) << "\n";

	return EXIT_SUCCESS;
}
