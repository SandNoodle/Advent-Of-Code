#include <iostream>
#include <fstream>

#include <cmath>
#include <cstdlib>
#include <numeric>
#include <algorithm>

#include <string>
#include <vector>

struct BestPosition
{
	int index;
	int fuelCost = std::numeric_limits<int>::max();
};

std::vector<int> GetPositionData(const char* file)
{
	std::ifstream inputFile(file);
	if(!inputFile.is_open()) return {};

	std::vector<int> positionData;

	std::string line;
	while(std::getline(inputFile, line, ','))
	{
		positionData.push_back(std::atoi(line.c_str()));
	}

	return positionData;
}

int StepFuelCost(int distance)
{
	return distance * (distance + 1) / 2;
}

int GetFuelCost(const std::vector<int> crabPositions, int destinationPosition)
{
	int fuelCost = 0;

	for(auto& crab : crabPositions)
	{
		fuelCost += StepFuelCost(std::abs(crab - destinationPosition));
	}

	return fuelCost;
}

int main(void)
{
	std::vector<int> positionData = GetPositionData("../../Data/crabmarines-position-data.txt");

	auto minmax = std::minmax_element(positionData.begin(), positionData.end());
	int minPosition = *minmax.first;
	int maxPosition = *minmax.second;

	BestPosition best;
	for(int i = minPosition; i <= maxPosition; ++i)
	{
		int currentPositionCost = GetFuelCost(positionData, i);
		if(currentPositionCost < best.fuelCost)
		{
			best.index = i;
			best.fuelCost = std::min(best.fuelCost, GetFuelCost(positionData, i));
		}
	}


	std::cout << "Position: " << best.index << " used least fuel: " << best.fuelCost << "\n";
	return EXIT_SUCCESS;
}
