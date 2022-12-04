#pragma once

#include <iostream>

#include <fstream>
#include <filesystem>

#include <string>

#include <vector>

#include <ranges>
#include <functional>
#include <algorithm>

#include <regex>
#include <chrono>
#include <type_traits>

/* ****************************************************************************
 * Defines
 *************************************************************************** */

#define PRINT(x) std::cout << x << std::endl

/* ****************************************************************************
 * Forward declarations
 *************************************************************************** */

/* --- Files --- */
std::string load_file(std::filesystem::path path) noexcept;

/* --- Parsing --- */
std::vector<std::string> create_vector(const std::string& data,
		char delimiter = '\n', bool allow_blanks = true) noexcept;

std::vector<std::string> create_vector(const std::string& data,
		std::string pattern) noexcept;

std::vector<int32_t> convert_to_int_vector(const std::vector<std::string>&
		vector) noexcept;

template<typename T>
size_t get_index_of_max_element(const std::vector<T> data, T value) noexcept;
template<typename T>
size_t get_index_of_min_element(const std::vector<T> data, T value) noexcept;

inline int32_t to_number(const std::string& s) noexcept;

inline bool is_range_overlap(int32_t x1, int32_t x2,
		int32_t y1, int32_t y2) noexcept;
inline bool is_range_fully_overlap(int32_t x1, int32_t x2,
		int32_t y1, int32_t y2) noexcept;

void trim(std::string& string) noexcept;
void trim_left(std::string& string) noexcept;
void trim_right(std::string& string) noexcept;

/* --- Error checking --  */
template<typename T, typename U>
bool check_result(T value, U expected) noexcept;

/* ****************************************************************************
 * Function impl
 *************************************************************************** */

std::string load_file(std::filesystem::path path) noexcept
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

std::vector<std::string> create_vector(const std::string& data,
		char delimiter, bool allow_blanks) noexcept
{
	std::vector<std::string> out;

	std::string line = std::string();
	std::stringstream ss(data);
	while(std::getline(ss, line, delimiter))
	{
		if(allow_blanks || line.size() > 0)
			out.push_back(line);
	}

	return out;
}

std::vector<std::string> create_vector(const std::string& data,
		std::string pattern) noexcept
{
	const std::regex reg(pattern);
	return { std::sregex_token_iterator(data.begin(), data.end(), reg, -1),
		std::sregex_token_iterator()};
}

std::vector<int32_t> convert_to_int_vector(const std::vector<std::string>&
		vector) noexcept
{
	std::vector<int32_t> out;
	out.reserve(vector.size());

	std::ranges::for_each(vector, [&out](const auto& v)
			{ out.push_back(to_number(v)); });
	return out;
}

template<typename T>
size_t get_index_of_max_element(const std::vector<T> data) noexcept
{
	return std::distance(data.begin(), std::ranges::max_element(data));
}

template<typename T>
size_t get_index_of_min_element(const std::vector<T> data) noexcept
{
	return std::distance(data.begin(), std::ranges::min_element(data));
}

int32_t to_number(const std::string& s) noexcept
{
	return std::atoi(s.c_str());
}

bool is_range_overlap(int32_t x1, int32_t y1,
		int32_t x2, int32_t y2) noexcept
{
	return (std::max(x1, x2) <= std::min(y1, y2));
}

bool is_range_fully_overlap(int32_t x1, int32_t y1,
		int32_t x2, int32_t y2) noexcept
{
	return ((x1 >= x2) && (y1 <= y2)) || ((x1 <= x2) && (y1 >= y2));
}

void trim(std::string& string) noexcept
{
	trim_left(string);
	trim_right(string);
}

void trim_left(std::string& string) noexcept
{
	const auto trim_func = [](const auto& c){
		return !std::isspace(c);
	};
	string.erase(string.begin(), std::ranges::find_if(string, trim_func));
}

void trim_right(std::string& string) noexcept
{
	const auto trim_func = [](const auto& c){
		return std::isspace(c);
	};
	string.erase(std::ranges::find_if(string, trim_func), string.end());
}

template<typename T, typename U>
bool check_result(T value, U expected) noexcept
{
	static_assert(std::is_integral_v<T>, "Value is not integral.");
	static_assert(std::is_integral_v<U>, "Value is not integral.");
	static_assert(sizeof(T) >= sizeof(U),
		"'value' size (in bytes) is not equal or greater than 'expected'");

	if(value != static_cast<T>(expected))
	{
		PRINT("[ERROR] Expected: " << expected << ", but got: " << value);
		return false;
	}

	return true;
}

/* ****************************************************************************
 * Classes
 *************************************************************************** */

class Timer
{
	public:
		Timer() : start(std::chrono::steady_clock::now()) { }
		~Timer()
		{
			auto end = std::chrono::steady_clock::now();
			std::chrono::duration<double> diff = end - start;
			PRINT("Execution took: " << diff.count() * 1000 << " ms.");
		}

	private:
		std::chrono::time_point<std::chrono::steady_clock> start;
};
