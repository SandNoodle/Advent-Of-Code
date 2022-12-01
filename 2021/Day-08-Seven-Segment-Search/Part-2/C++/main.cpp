#include <iostream>
#include <fstream>
#include <sstream>

#include <exception>
#include <algorithm>
#include <numeric>

#include <vector>
#include <string>

struct LineData
{
	std::vector<std::string> referenceStrings;
	std::vector<std::string> outputStrings;
};

struct Data
{
	std::vector<LineData> linesData;
};

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

Data GetData(const char* file)
{
	std::ifstream inputFile(file);
	if(!inputFile.is_open()) throw std::exception("File not found!");

	Data data;
	std::string line;
	while(std::getline(inputFile, line, '\n'))
	{
		/* size_t splitIndex = line.find("|"); */
		/* line.erase(line.begin(), line.begin() + splitIndex + 2); // 2 -> Corrections for | and <space> */
		/* std::vector<std::string> outputLine = SplitStringToVector(line); */
		/* outputStrings.insert(outputStrings.end(), outputLine.begin(), outputLine.end()); */
	}

	return data;
}

std::vector<int> DecodeLine(const LineData &lineData)
{
	std::vector<int> decodedLine;



	return decodedLine;
}

std::vector<int> DecodeAll(const Data &data)
{
	std::vector<int> decodedOutputs;

	return decodedOutputs;
}

uint32_t GetOutputSum(const std::vector<int> &decodedOutputs)
{
	return std::accumulate(decodedOutputs.begin(), decodedOutputs.end(), 0);
}

int main(void)
{
	Data inputData = GetData("../../Data/segment-display-test-data.txt");
	std::vector<int> decodedOutputs = DecodeAll(inputData);
	uint32_t outputSum = GetOutputSum(decodedOutputs);

	std::cout << "Sum of outputs: " << outputSum << "\n";

	return EXIT_SUCCESS;
}
