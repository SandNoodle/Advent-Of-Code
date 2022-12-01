#include <iostream>
#include <fstream>
#include <stdint.h>
#include <type_traits>
#include <vector>
#include <string>
#include <cmath>

typedef char byte;

// ------------------------------------------------

std::vector<std::vector<byte>> LoadSubmarineDiagnosticData(const char* file)
{
	std::fstream diagnosticFile(file);

	std::vector<std::vector<byte>> submarineDiagnosticData;
	if(diagnosticFile.is_open())
	{
		std::string line;
		while(diagnosticFile >> line)
		{
			std::vector<byte> binaryData(line.begin(), line.end());
			submarineDiagnosticData.push_back(binaryData);
		}
	}

	return submarineDiagnosticData;
}

// ------------------------------------------------

int ConvertBitToInt(byte value)
{
	return value == '1' ? 1 : 0;
}

int ConvertToInt(const std::vector<byte> &bitset)
{
	int value = 0;
	for(int index = 0; index < bitset.size(); ++index)
	{
		int convertedValue = ConvertBitToInt(bitset[bitset.size() - index - 1]);
		value |= convertedValue << index;
	}

	return value;
}

int GetBitInMajority(const std::vector<byte> &columnVector, int bitCriteria)
{
	int oneCount = 0;
	int zeroCount = 0;

	for(int i = 0; i < columnVector.size(); i++)
	{
		if(ConvertBitToInt(columnVector.at(i)) == 1)
			oneCount++;
		else
			zeroCount++;
	}

	if(oneCount == zeroCount) return bitCriteria;
	if(bitCriteria == 1) return oneCount > zeroCount ? 1 : 0;

	return oneCount > zeroCount ? 0 : 1;
}

std::vector<byte> ConstructColumnDataVector(const std::vector<std::vector<byte>> &submarineDiagnosticData, int columnIndex)
{
	std::vector<byte> columnData;
	for(int dataRow = 0; dataRow < submarineDiagnosticData.size(); dataRow++)
	{
		columnData.push_back(submarineDiagnosticData[dataRow][columnIndex]);
	}

	return columnData;
}

// ------------------------------------------------

void RemoveInvalidData(std::vector<std::vector<byte>> &diagnosticData, int bitCriteria, int columnIndex)
{
	std::vector<std::vector<byte>> validData;

	for(int i = 0; i < diagnosticData.size(); ++i)
	{
		if(ConvertBitToInt(diagnosticData.at(i).at(columnIndex)) == bitCriteria)
		{
			validData.push_back(diagnosticData.at(i));
		}
	}

	diagnosticData = validData;
}

std::vector<byte> CalculateRating(const std::vector<std::vector<byte>> &submarineDiagnosticData, int bitCriteria)
{
	std::vector<std::vector<byte>> diagnosticData(submarineDiagnosticData);

	int columnIndex = 0;
	while(diagnosticData.size() > 1)
	{
		std::vector<byte> columnVector = ConstructColumnDataVector(diagnosticData, columnIndex);

		RemoveInvalidData(diagnosticData, GetBitInMajority(columnVector, bitCriteria), columnIndex);

		columnIndex++;
	}

	return diagnosticData.at(0);
}

// ------------------------------------------------

int main(void)
{
	std::vector<std::vector<byte>> submarineDiagnosticData = LoadSubmarineDiagnosticData("../../Data/submarine_diagnostics_data.txt");

	std::vector<byte> binaryOxygenRating = CalculateRating(submarineDiagnosticData, 1);
	std::vector<byte> binaryScrubberRating = CalculateRating(submarineDiagnosticData, 0);

	int oxygenRating = ConvertToInt(binaryOxygenRating);
	int scrubberRating = ConvertToInt(binaryScrubberRating);
	int lifeSupportRating = oxygenRating * scrubberRating;

	std::cout << "Oxygen rating: " << oxygenRating << "\n";
	std::cout << "CO2 Scrubber rating: " << scrubberRating << "\n";
	std::cout << "Life Support rating: " << lifeSupportRating << "\n";

	return EXIT_SUCCESS;
}
