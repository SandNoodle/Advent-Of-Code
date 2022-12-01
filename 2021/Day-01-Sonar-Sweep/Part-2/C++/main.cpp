#include <iostream>
#include <iterator>
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

bool CanSlidingMeasurementWindowBeCreated(const std::vector<int> &dataArray, int windowSize, int offset)
{
	int startIndex = offset;
	int endIndex = offset + windowSize;

	if(startIndex > dataArray.size()) return false;
	if(endIndex > dataArray.size()) return false;

	return true;
}

std::vector<int> CreateSlidingMeasurementWindow(const std::vector<int> &dataArray, int windowSize, int offset)
{
	if(!CanSlidingMeasurementWindowBeCreated(dataArray, windowSize, offset))
	{
		return std::vector<int>();
	}

	int startIndex = offset;
	int endIndex = offset + windowSize;

	return std::vector<int>(&dataArray[startIndex], &dataArray[endIndex]);
}

std::vector<std::vector<int>> CreateSlidingMeasurementWindows(const std::vector<int> &dataArray, int windowSize)
{
	std::vector<std::vector<int>> slidingWindows;

	for(int offset = 0; offset < dataArray.size(); offset++)
	{
		if(CanSlidingMeasurementWindowBeCreated(dataArray, windowSize, offset))
		{
			slidingWindows.push_back(CreateSlidingMeasurementWindow(dataArray, windowSize, offset));
		}
	}

	return slidingWindows;
}

int SumSlidingMeasurementWindow(const std::vector<int> &slidingWindow)
{
	int slidingWindowSum = 0;

	for(auto& sonarData : slidingWindow)
	{
		slidingWindowSum += sonarData;
	}

	return slidingWindowSum;
}

bool CanMeasurementWindowBeSummed(const std::vector<int> &slidingWindow, int windowSize)
{
	return slidingWindow.size() == windowSize;
}

std::vector<int> SumSlidingMeasurementWindows(const std::vector<std::vector<int>> &slidingWindows, int windowSize)
{
	std::vector<int> summedSlidingWindows;
	for(auto& slidingWindow : slidingWindows)
	{
		if(CanMeasurementWindowBeSummed(slidingWindow, windowSize))
		{
			int slidingWindowSum = SumSlidingMeasurementWindow(slidingWindow);
			summedSlidingWindows.push_back(slidingWindowSum);
		}
	}

	return summedSlidingWindows;
}

bool IsDepthIncreasing(int previousMeasurement, int currentMeasurement)
{
	return currentMeasurement > previousMeasurement;
}

int CalculateDepthIncreaseCount(const std::vector<int> &summedSlidingWindows)
{
	int increaseCount = 0;

	for(int i = 1; i < summedSlidingWindows.size(); i++)
	{
		int previousMeasurement = summedSlidingWindows[i - 1];
		int currentMeasurement = summedSlidingWindows[i];
		if(IsDepthIncreasing(previousMeasurement, currentMeasurement))
		{
			increaseCount++;
		}
	}

	return increaseCount;
}

int main(void)
{
	/* std::vector<int> sonarReportData = { 199, 200, 208, 210, 200, 207, 240, 269, 260, 263 }; */
	std::vector<int> sonarReportData = LoadSonarData("../../Data/submarine_sonar_report_file.txt");

	int windowSize = 3;
	std::vector<std::vector<int>> slidingMeasurementWindows = CreateSlidingMeasurementWindows(sonarReportData, windowSize);
	std::vector<int> summedSlidingMeasurementWindows = SumSlidingMeasurementWindows(slidingMeasurementWindows, windowSize);

	int depthIncreaseCount = CalculateDepthIncreaseCount(summedSlidingMeasurementWindows);

	std::cout << "Times the depth increased relative to previous measurement block: " << depthIncreaseCount  << std::endl;

	return EXIT_SUCCESS;
}
