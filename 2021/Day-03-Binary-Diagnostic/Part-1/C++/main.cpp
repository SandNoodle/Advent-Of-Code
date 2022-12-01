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

void Flip(std::vector<byte> &vector, int index)
{
	vector[index] = vector[index] == '0' ? '1' : '0';
}

bool IsOnBitInMajority(const std::vector<byte> &columnData)
{
	int onBitCount = 0;
	int offBitCount = 0;

	for(int i = 0; i < columnData.size(); i++)
	{
		columnData[i] == '1' ? onBitCount++ : offBitCount++;
	}

	return onBitCount >= offBitCount;
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

std::vector<byte> CalculateGammaRate(const std::vector<std::vector<byte>> &submarineDiagnosticData)
{
	std::vector<byte> gammaRate;

	int sampleLength = submarineDiagnosticData[0].size();
	for(int index = 0; index < sampleLength; index++)
	{
		std::vector<byte> columnData = ConstructColumnDataVector(submarineDiagnosticData, index);
		gammaRate.push_back(IsOnBitInMajority(columnData) ? '1' : '0');
	}

	return gammaRate;
}

std::vector<byte> CalculateEpsilonRate(const std::vector<byte> &gammaRate)
{
	std::vector<byte> epsilonRate(gammaRate);
	for(int i = 0; i < gammaRate.size(); ++i)
	{
		Flip(epsilonRate, i);
	}

	return epsilonRate;
}

// ------------------------------------------------

int main(void)
{
	std::vector<std::vector<byte>> submarineDiagnosticData = LoadSubmarineDiagnosticData("../../Data/submarine_diagnostics_data.txt");

	std::vector<byte> binaryGammaRate = CalculateGammaRate(submarineDiagnosticData);
	std::vector<byte> binaryEpsilonRate = CalculateEpsilonRate(binaryGammaRate);

	int gammaRate = ConvertToInt(binaryGammaRate);
	int epsilonRate = ConvertToInt(binaryEpsilonRate);
	int powerConsumption = gammaRate * epsilonRate;

	std::cout << "Gamma rate: " << gammaRate << "\n";
	std::cout << "Epsilon rate: " << epsilonRate << "\n";
	std::cout << "Power consumption: " << powerConsumption << "\n";

	return EXIT_SUCCESS;
}
