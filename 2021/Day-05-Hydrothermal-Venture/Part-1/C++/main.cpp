#include <iostream>

#include <fstream>
#include <filesystem>

#include <string>
#include <string_view>

#include <vector>
#include <unordered_map>

#include <ranges>
#include <algorithm>

/* ****************************************************************************
 * Defines
 *************************************************************************** */

struct coordinate
{
	uint32_t x = 0;
	uint32_t y = 0;

	coordinate() = default;
	coordinate(uint32_t x, uint32_t y) : x(x), y(y) { }

	bool operator==(const coordinate& c) const
	{
		return (x == c.x) && (y == c.y);
	}

};

std::ostream& operator<<(std::ostream& os, const coordinate& c)
{
	return os << "[" << c.x << ", " << c.y << "]";
}

template<>
struct std::hash<coordinate>
{
	std::size_t operator()(const coordinate& c) const {
		std::size_t h1 = std::hash<uint32_t>()(c.x);
		std::size_t h2 = std::hash<uint32_t>()(c.y);

		return h1 ^ h2;
	}
};

using file_data = std::vector<std::string>;
using coord_freq = std::unordered_map<coordinate, uint32_t>;

/* ****************************************************************************
 * Functions
 *************************************************************************** */

std::vector<std::string> split_string(const std::string& str, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream iss(str);
	while(std::getline(iss, token, delimiter))
	{
		tokens.push_back(token);
	};
	return tokens;
}

file_data read_file(std::filesystem::path path)
{
	if(!std::filesystem::exists(path))
	{
		throw std::runtime_error("File does not exist.");
	}

	constexpr auto read_size = std::size_t(4096);
	auto stream = std::ifstream(path);
	stream.exceptions(std::ios_base::badbit);

	auto file_data = std::string();
	auto buffer = std::string(read_size, '\0');
	while(stream.read(&buffer[0], read_size))
	{
		file_data.append(buffer, 0, stream.gcount());
	}
	file_data.append(buffer, 0, stream.gcount());

	return split_string(file_data, '\n');
}

coordinate get_coordinate(const std::vector<std::string>& v)
{
	return coordinate(std::stoi(v[0]), std::stoi(v[1]));
}

std::vector<coordinate> create_lines(coordinate a,
		coordinate b)
{
	std::vector<coordinate> out_data;

	const auto start_x = std::min(a.x, b.x);
	const auto stop_x = std::max(a.x, b.x);

	const auto start_y = std::min(a.y, b.y);
	const auto stop_y = std::max(a.y, b.y);

	if(a.x == b.x)
	{
		for(uint32_t i = start_y; i <= stop_y; ++i)
		{
			out_data.push_back({a.x, i});
		}
		return out_data;
	}

	if(a.y == b.y)
	{
		for(uint32_t i = start_x; i <= stop_x; ++i)
		{
			out_data.push_back({i, a.y});
		}
		return out_data;
	}

	return { };
}

coord_freq parse_data(const file_data& file_data)
{
	coord_freq out_data;

	for(size_t index = 0; index < file_data.size(); ++index)
	{
		const auto line = file_data.at(index);
		const auto tokens = split_string(line, ' ');

		coordinate start = get_coordinate(split_string(tokens[0], ','));
		coordinate stop = get_coordinate(split_string(tokens[2], ','));

		auto coordinates = create_lines(start, stop);
		if(coordinates.empty()) {
			continue;
		}

		std::ranges::for_each(coordinates, [&out_data](const auto& c)
			{
				auto it = out_data.find(c);
				if(it != out_data.end())
				{
					it->second++;
				}
				else
				{
					out_data.insert(std::make_pair(c, 1));
				}
			});
	}

	return out_data;
}

uint32_t overlap_count(const coord_freq& coords)
{
	auto count = 0;
	std::for_each(coords.begin(), coords.end(), [&count](const auto& c){
		if(c.second >= 2) count++;
	});

	return count;
}

/* ****************************************************************************
 * Main program
 *************************************************************************** */

int main(void)
{
	auto file_data   = read_file("../../Data/hydrothermal-vents-data.txt");
	auto coordinates = parse_data(file_data);
	auto overlaps    = overlap_count(coordinates);

	std::cout << overlaps << std::endl;

	return 0;
}
