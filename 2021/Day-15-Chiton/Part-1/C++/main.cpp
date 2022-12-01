#include <iostream>
#include <fstream>
#include <stdexcept>

#include <limits>

#include <set>
#include <stdint.h>

// -----
typedef uint64_t u64;
typedef uint32_t u32;

typedef int64_t i64;
typedef int32_t i32;
// -----

struct Cavern
{
};

struct Node
{
	u64 x;
	u64 y;
};

void GetNeightbours()
{
	throw std::exception("GetNeightbours is not implemented yet. Implement: Return Type, Input parameters and logic");
}

// Dijkstra's alghoritm (https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm)
uint32_t GetPath(Cavern cavern)
{
	uint32_t finalRisk = 0;

	// Mark all nodes unvisited
	std::set<Node> unvisited;

	// Assign every node tenative distance of INFINITY
	for()
	{
		.distance = std::numeric_limits<int>::max(); // INT_MAX is consiered an infinity
	}

	// Assign source's index tenative distance of 0
	.distance = 0;

	// Set the initial node as current
	current = initial;

	// LOOP (SEE "!!!" for exit condition):
	//	For current node consider all univisited neighbours and calculate thier tenative distances through current node
	// 	Remove current node from unvisited nodes
	// 	Choose neighbour with least tenative distance as a new current node

	// !!! Alghoritm finishes if:
	// --- Destination node was selected as visited
	// --- Smallest tenative distance equals to INFINITY)

	while(!unvisited.empty())
	{

	}

	return finalRisk;
}

int main(void)
{
	Cavern cavern;
	uint32_t finalRisk = GetPath(cavern);

	std::cout << "Path with least risk: " << finalRisk << "\n";

	return EXIT_SUCCESS;
}
