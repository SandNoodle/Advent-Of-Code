#include <iostream>
#include <vector>
#include <fstream>

std::vector<int> LoadSonarData(const char* file)
{
	std::fstream inputFile(file);

	int depthData;
	std::vector<int> sonarData;
	if(inputFile.is_open())
	{
		while(inputFile >> depthData)
		{
			sonarData.push_back(depthData);
		}
	}

	return sonarData;
}

bool IsDepthIncreasing(int previousMeasurement, int currentMeasurement)
{
	return currentMeasurement > previousMeasurement;
}

int CalculateDepthIncreaseCount(const std::vector<int> &reportArray)
{
	if (reportArray.size() <= 1) 
	{
		return 0;
	}

	int increaseCount = 0;

	for(int i = 1; i < reportArray.size(); i++)
	{
		int previousMeasurement = reportArray[i - 1];
		int currentMeasurement = reportArray[i];
		if(IsDepthIncreasing(previousMeasurement, currentMeasurement))
		{
			increaseCount++;
		}
	}

	return increaseCount;
}

int main(void)
{
	std::vector<int> sonarReportArray = LoadSonarData("../../Data/submarine_sonar_report_file.txt");

	int depthIncreaseCount = CalculateDepthIncreaseCount(sonarReportArray);

	std::cout << "Times the depth increased relative to previous measurement: " << depthIncreaseCount  << std::endl;

	return EXIT_SUCCESS;
}
