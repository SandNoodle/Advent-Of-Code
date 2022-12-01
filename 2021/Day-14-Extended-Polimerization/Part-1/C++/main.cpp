#include <iostream>
#include <fstream>

#include <string>
#include <vector>
#include <unordered_map>

struct PolymerData
{
	std::vector<char> sequence;
	std::unordered_map<std::string, char> polymerTemplate;
};

struct PolymerAnswer
{
	uint32_t leastCommon;
	uint32_t mostCommon;
};

PolymerData GetDataFromFile(const char* file)
{
	PolymerData data;



	return data;
}

PolymerAnswer Calculate(const PolymerData &polymerData, uint32_t stepCount)
{
	PolymerAnswer answer;

	// Extract values to variables - make it neat!
	std::vector<char> initialSequence = polymerData.sequence;
	std::unordered_map<std::string, char> polymerTemplate = polymerData.polymerTemplate;
	std::unordered_map<char, uint32_t> frequencyMap;

	for(int i = 0; i < stepCount; ++i)
	{
		std::

	}

	return answer;
}

int main(void)
{
	const int maxSteps = 10;

	PolymerData polymerData = GetDataFromFile("../../Data/polymerization-test-data.txt");

	// Output
	std::cout << "Length after " << maxSteps << ": "  << "\n";
	std::cout << "Least coommon element is: '" << "' with value of " << "\n";
	std::cout << "Most coommon element is: '" << "' with value of " << "\n";
	std::cout << "Answer: \n";

	return EXIT_SUCCESS;
}
