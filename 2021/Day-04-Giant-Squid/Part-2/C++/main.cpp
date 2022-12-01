#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <numeric>
#include <algorithm>
#include <stdint.h>
#include <vector>
#include <string>

#define BOARD_SIZE 5

struct Board
{
	int cells[BOARD_SIZE][BOARD_SIZE];
	bool marks[BOARD_SIZE][BOARD_SIZE] = { false };
	uint32_t score;
};

struct Game
{
	std::vector<int> sequence;
	std::vector<Board> boards;
};

std::vector<int> GetIntVectorByDelimiter(std::string lineString, char delimiter)
{
	std::vector<int> sequence;
	std::stringstream ss(lineString);
	for(int i; ss >> i;)
	{
		sequence.push_back(i);
		if(ss.peek() == delimiter)
		{
			ss.ignore();
		}
	}

	return sequence;
}

std::vector<int> GetBingoSequence(std::string lineString)
{
	return GetIntVectorByDelimiter(lineString, ',');
}

Board GetBoard(const std::vector<std::string> &boardStrings)
{
	Board board;
	for(int lineIndex = 0; lineIndex < BOARD_SIZE; lineIndex++)
	{
		std::vector<int> lineSequence = GetIntVectorByDelimiter(boardStrings.at(lineIndex), ' ');
		for(int col = 0; col < BOARD_SIZE; col++)
		{
			board.cells[lineIndex][col] = lineSequence.at(col);
		}
	}

	return board;
}

// Note: This is horrible code, but it's late and I'm fed up with this
// It works.
Game GetData(const char *file)
{
	std::ifstream inputFile(file);
	if(!inputFile.is_open()) throw std::runtime_error("File not found!");

	Game gameData;

	bool sequenceLoaded = false;
	int boardLineIndex = 0;
	std::string line;
	std::vector<std::string> boardPattern;
	while(std::getline(inputFile, line, '\n'))
	{
		if(line == "") continue;
		if(!sequenceLoaded)
		{
			sequenceLoaded = true;
			gameData.sequence = GetBingoSequence(line);
			continue;
		}

		boardPattern.push_back(line);

		if(boardPattern.size() == 5)
		{
			Board board = GetBoard(boardPattern);
			gameData.boards.push_back(board);
			boardPattern.clear();
		}
	}

	return gameData;
}

void Mark(Board &board, int value)
{
	for(int i = 0; i < BOARD_SIZE; ++i)
	{
		for(int j = 0; j < BOARD_SIZE; ++j)
		{
			if(board.cells[i][j] == value)
			{
				board.marks[i][j] = true;
			}
		}
	}
}

bool CheckBoard(const Board &board)
{
	// Easier way of checking - thanks Tsoding! (https://gitlab.com/tsoding/aoc-2021/-/blob/master/Home/AOC-2021/04/Main.HC)
	int j;
	for(int i = 0; i < BOARD_SIZE; ++i)
	{
		// Horizontal
		j = 0;
		while(j < BOARD_SIZE && board.marks[i][j]) { ++j; }
		if(j >= BOARD_SIZE) return true;

		// Vertical
		j = 0;
		while(j < BOARD_SIZE && board.marks[j][i]) { ++j; }
		if(j >= BOARD_SIZE) return true;
	}

	return false;
}

uint32_t GetScore(const Board &board, int winningNumber)
{
	int sum = 0;
	for(int i = 0; i < BOARD_SIZE; ++i)
	{
		for(int j = 0; j < BOARD_SIZE; ++j)
		{
			if(!board.marks[i][j])
			{
				sum += board.cells[i][j];
			}
		}
	}
	return sum * winningNumber;
}

int main(void)
{
	/* Game gameData = GetData("../../Data/bingo_subsystem_data.txt"); */
	Game gameData = GetData("../../Data/bingo_subsystem_data.txt");

	// Note: Clarity
	std::vector<int> bingoSequence = gameData.sequence;
	std::vector<Board> boards = gameData.boards;
	int winCount = 0;

	for(int sequenceIndex = 0; sequenceIndex < bingoSequence.size(); ++sequenceIndex)
	{
		for(int boardIndex = 0; boardIndex < boards.size(); ++boardIndex)
		{
			if(!CheckBoard(boards.at(boardIndex)))
			{
				Mark(boards.at(boardIndex), bingoSequence.at(sequenceIndex));
				if(CheckBoard(boards.at(boardIndex)))
				{
					winCount++;
					if(winCount >= boards.size())
					{
						std::cout << "Last winning board: " << GetScore(boards.at(boardIndex), bingoSequence.at(sequenceIndex));
					}

				}
			}
		}

	}


	return EXIT_SUCCESS;
}
