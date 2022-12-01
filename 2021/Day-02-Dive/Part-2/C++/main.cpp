#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>

// ----------------------------------------

void LoadSumbarinePositionData(	std::vector<int> &horizontalMovement,
		std::vector<int> &aimMovement,
		const char* file)
{
	std::fstream positionDataFile(file);

	if(positionDataFile.is_open())
	{
		std::string token;
		int value;
		int aimValue = 0;
		while(positionDataFile >> token >> value)
		{
			switch(token[0])
			{
				case 'f': 
					horizontalMovement.push_back(value);
					aimMovement.push_back(aimValue);
					break;
				case 'u':
					aimValue -= value;
					break;
				case 'd':
					aimValue += value;
					break;
				default:
					break;
			}
		}
	}
}

// ----------------------------------------

int CalculateDepth(int currentHorizontalPosition, int currentAim)
{
	return currentHorizontalPosition * currentAim;
}

// ----------------------------------------

int CalculateFinalDepth (const std::vector<int> &horizontalMovement, const std::vector<int> &aimMovement)
{
	int finalDepth = 0;

	for(int i = 0; i < horizontalMovement.size(); i++)
	{
		finalDepth += CalculateDepth(horizontalMovement[i], aimMovement[i]);
	}

	return finalDepth;
}

int CalculateFinalHorizontalPosition(const std::vector<int> &horizontalMovement)
{
	int finalPosition = 0;

	for(auto& position : horizontalMovement)
	{
		finalPosition += position;
	}

	return finalPosition;
}

int CalculateFinalPosition(int finalHorizontalPosition, int finalDepth)
{
	return finalHorizontalPosition * finalDepth;
}

// ----------------------------------------

int main(void)
{
	std::vector<int> horizontalMovement;
	std::vector<int> aimMovement;

	LoadSumbarinePositionData(horizontalMovement, aimMovement, "../../Data/submarine_commands_data.txt");

	int finalHorizontalPosition = CalculateFinalHorizontalPosition(horizontalMovement);
	int finalDepth = CalculateFinalDepth(horizontalMovement, aimMovement);
	int finalCourse = finalHorizontalPosition * finalDepth;

	std::cout << "Final horizontal position: " << finalHorizontalPosition << "\n"; 
	std::cout << "Final depth: " << finalDepth << "\n"; 
	std::cout << "Multiplication of both: " << finalCourse << "\n";

	return EXIT_SUCCESS;
}
