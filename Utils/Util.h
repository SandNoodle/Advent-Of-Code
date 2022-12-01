#pragma once

#include <iostream>

#include <fstream>
#include <filesystem>

#include <string>

#include <vector>

#include <ranges>
#include <functional>
#include <algorithm>

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
std::string load_file(std::filesystem::path path);

/* --- Parsing --- */
template<typename T>
std::vector<T> create_vector(const std::string& data, std::string delimiter,
		bool allow_blanks = true);

template<typename T, typename Comparator>
size_t get_index_of_element(const std::vector<T> data, T value, Comparator comp);
template<typename T>
size_t get_index_of_max_element(const std::vector<T> data, T value);
template<typename T>
size_t get_index_of_min_element(const std::vector<T> data, T value);

void trim(std::string& string);
void trim_left(std::string& string);
void trim_right(std::string& string);

/* --- Error checking --  */
template<typename T, typename U>
bool check_result(T value, U expected);

/* ****************************************************************************
 * Function impl
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

template<typename T>
std::vector<T> create_vector(const std::string& data, std::string delimiter, bool allow_blanks)
{
	std::vector<T> out;

/* 	auto line = std::string(); */
/* 	while(std::getline(data, line, delimiter)) */
/* 	{ */
/* 		if(allow_blanks || line.size() > 0) */
/* 			out.push_back(line); */
/* 	} */

	return out;
}

template<typename T, typename Comparator>
size_t get_index_of_element(const std::vector<T> data, T value, Comparator comp)
{
	static_assert(std::is_integral_v<T>, "Element type is not integral.");

	/* auto it = std::ranges::; */

	/* 	return std::distance(data.begin(), it); */

}

template<typename T>
size_t get_index_of_max_element(const std::vector<T> data)
{
	return std::distance(data.begin(), std::ranges::max_element(data));
}

template<typename T>
size_t get_index_of_min_element(const std::vector<T> data)
{
	return std::distance(data.begin(), std::ranges::min_element(data));
}

void trim(std::string& string)
{
	trim_left(string);
	trim_right(string);
}

void trim_left(std::string& string)
{
	const auto trim_func = [](const auto& c){
		return !std::isspace(c);
	};
	string.erase(string.begin(), std::ranges::find_if(string, trim_func));
}

void trim_right(std::string& string)
{
	const auto trim_func = [](const auto& c){
		return std::isspace(c);
	};
	string.erase(std::ranges::find_if(string, trim_func), string.end());
}

template<typename T, typename U>
bool check_result(T value, U expected)
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
