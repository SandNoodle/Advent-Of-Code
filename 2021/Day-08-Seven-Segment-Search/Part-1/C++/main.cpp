#include <iostream>
#include <fstream>
#include <sstream>

#include <exception>
#include <algorithm>

#include <vector>
#include <string>

std::vector<std::string> SplitStringToVector(const std::string &inputString)
{
	std::vector<std::string> outputVector;

	std::stringstream ss(inputString);
	std::string token;
	while(std::getline(ss, token, ' '))
	{
		outputVector.push_back(token);
	}

	return outputVector;
}

std::vector<std::string> GetData(const char* file)
{
	std::ifstream inputFile(file);
	if(!inputFile.is_open()) throw std::exception("File not found!");

	std::vector<std::string> outputStrings;
	std::string line;
	while(std::getline(inputFile, line, '\n'))
	{
		size_t splitIndex = line.find("|");
		line.erase(line.begin(), line.begin() + splitIndex + 2); // 2 -> Corrections for | and <space>
		std::vector<std::string> outputLine = SplitStringToVector(line);
		outputStrings.insert(outputStrings.end(), outputLine.begin(), outputLine.end());
	}

	return outputStrings;
}

bool IsUnique(const std::string &data)
{
	// Number -> Segment-Count
	// 1      -> 2
	// 7      -> 3
	// 4      -> 4
	// 8      -> 7
	int size = data.size();
	if(size == 2 || size == 3 || size == 4 || size == 7)
	{
		return true;
	}
	return false;
}

uint32_t GetOutputSum(const std::vector<std::string> &outputStrings)
{
	return std::count_if(outputStrings.begin(), outputStrings.end(), IsUnique);
}

int main(void)
{
	std::vector<std::string> outputStrings = GetData("../../Data/segment-display-data.txt");
	uint32_t uniqueCount = GetOutputSum(outputStrings);

	std::cout << "Times 1, 4, 7 or 8 appear: " << uniqueCount << "\n";

	return EXIT_SUCCESS;
}
