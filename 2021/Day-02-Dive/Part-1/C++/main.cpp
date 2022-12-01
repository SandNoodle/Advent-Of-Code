#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// ----------------------------------------

void LoadSumbarinePositionData(	std::vector<int> &horizontalMovement,
				std::vector<int> &increaseDepthMovement,
				std::vector<int> &decreaseDepthMovement,
				const char* file)
{
	std::fstream positionDataFile(file);

	if(positionDataFile.is_open())
	{
		std::string token;
		int value;
		while(positionDataFile >> token >> value)
		{
			switch(token[0])
			{
				case 'f': 
					horizontalMovement.push_back(value);
					break;
				case 'u':
					decreaseDepthMovement.push_back(value);
					break;
				case 'd':
					increaseDepthMovement.push_back(value);
					break;
				default:
					break;
			}
		}
	}
}

// ----------------------------------------

int CalculatePosition(const std::vector<int> &movement)
{
	int finalPosition = 0;

	for(auto& position : movement)
	{
		finalPosition += position;
	}

	return finalPosition;
}

// ----------------------------------------

int CalculateVerticalPosition(const std::vector<int> &increaseDepthMovement, const std::vector<int> &decreaseDepthMovement)
{
	int increaseDepthPosition = CalculatePosition(increaseDepthMovement);
	int decreaseDepthPosition = CalculatePosition(decreaseDepthMovement);
	int finalDepthPosition = increaseDepthPosition - decreaseDepthPosition;

	return finalDepthPosition > 0 ? finalDepthPosition : 0;
}

// ----------------------------------------

int main(void)
{
	std::vector<int> horizontalMovement;
	std::vector<int> increaseDepthMovement;
	std::vector<int> decreaseDepthMovement;

	LoadSumbarinePositionData(horizontalMovement, 
				increaseDepthMovement, 
				decreaseDepthMovement, 
				"../../Data/submarine_commands_data.txt");


	int finalHorizontalPosition = CalculatePosition(horizontalMovement);
	int finalVerticalPosition = CalculateVerticalPosition(increaseDepthMovement, decreaseDepthMovement);
	int finalCourse = finalHorizontalPosition * finalVerticalPosition;

	std::cout << "Final horizontal position: " << finalHorizontalPosition << "\n";
	std::cout << "Final vertical position: " << finalVerticalPosition << "\n";
	std::cout << "Multiplication of both: " << finalCourse << "\n";

	return EXIT_SUCCESS;
}
