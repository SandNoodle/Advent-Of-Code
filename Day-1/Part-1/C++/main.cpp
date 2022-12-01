#include <iostream>

#include <fstream>
#include <filesystem>

#include <string>
#include <string_view>

#include <vector>

#include <ranges>
#include <algorithm>

#include <cstdint>
#include <cstdlib>

/* ***************************************************************************
 * Defines
 *************************************************************************** */

#define PRINT(x) std::cout << x << std::endl;

/* ***************************************************************************
 * Forward definitions
 *************************************************************************** */

std::string load_file(std::filesystem::path path);
std::vector<int32_t> get_elves(const std::string& data);

/* ***************************************************************************
 * Main program
 *************************************************************************** */

int main(void)
{
	auto file_data = load_file("../../Data/data.txt");
	auto elves = get_elves(file_data);
	auto index = std::ranges::max_element(elves);

	PRINT(*index);
	return 0;
}

/* ***************************************************************************
 * Functions
 *************************************************************************** */

std::string load_file(std::filesystem::path path)
{
	constexpr auto read_size = std::size_t(4096);

	auto stream = std::ifstream(path);
	stream.exceptions(std::ios::badbit);

	auto file_data = std::string();
	auto buffer = std::string(read_size, '\0');
	while(stream.read(&buffer[0], read_size))
	{
		file_data.append(buffer, 0, stream.gcount());
	}
	file_data.append(buffer, 0, stream.gcount());

	return file_data;
}

std::vector<int32_t> get_elves(const std::string& data)
{
	std::vector<int32_t> elves(1, 0);

	int32_t index = 0;
	std::string line = std::string();
	std::stringstream ss(data);
	while(std::getline(ss, line, '\n'))
	{
		if(line.empty())
		{
			index++;
			elves.push_back(0);
			continue;
		}

		elves[index] += std::atoi(line.c_str());
	}

	return elves;
}
