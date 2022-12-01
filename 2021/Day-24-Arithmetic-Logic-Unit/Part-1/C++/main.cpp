#include <iostream>

#include <cmath>
#include <cstdint>
#include <algorithm>
#include <functional>

#include <fstream>
#include <filesystem>

#include <string>
#include <string_view>

#include <vector>

/* ***************************************************************************
 * Defines
 *************************************************************************** */

#define PRINT(x) std::cout << x << std::endl

using file_path = std::filesystem::path;

using instruction_function = std::function<void(int32_t, int32_t)>;

struct alu_t
{
	int32_t w = 0;
	int32_t x = 0;
	int32_t y = 0;
	int32_t z = 0;
};

struct instruciton_t
{
	int32_t a;
	int32_t b;
	instruction_function func;
};

using instruction_list = std::vector<instruction_function>;

std::ostream& operator<<(std::ostream& os, const alu_t& a)
{
	return os << "["
		<< a.w << ", "
		<< a.x << ", "
		<< a.y << ", "
		<< a.z << "]"
		<< std::endl;
}

/* ***************************************************************************
 * Declarations
 *************************************************************************** */

instruction_list parse_file(file_path);
instruciton parse_instruction(const std::string&);

void execute_instructions(alu_t&, instruction_list);

void inp_instruction(int32_t& a, int32_t value);
void add_instruction(int32_t& a, int32_t b);
void mul_instruction(int32_t& a, int32_t b);
void div_instruction(int32_t& a, int32_t b);
void mod_instruction(int32_t& a, int32_t b);
void eql_instruction(int32_t& a, int32_t b);

/* ***************************************************************************
 * Main Program
 *************************************************************************** */

int main(void)
{
	alu_t alu;

	PRINT(alu);

	return 0;
}

/* ***************************************************************************
 * Function Impl
 *************************************************************************** */

instruction_list parse_file(file_path path)
{
	if(!std::filesystem::exists(path))
	{
		throw std::runtime_error("Failed to load the file.");
	}

	instruction_list instructions;

	std::ifstream fs(file_path);
	std::string token;
	while(std::getline(fs, token))
	{
		instructions.push_back(parse_instruction(token));
	}

	return instructions;
}

instruciton parse_instruction(const std::string& line)
{
	instruction_t instruction;
	instruction.

	return instruction;
}

void execute_instructions(alu_t& alu, const instruction_list& il)
{
	auto execute_instruciton = [&alu](const auto& instruction)
	{
		instruction(input, value);
	};

	std::for_each(il.begin(), il.end(), execute_instruciton);
}

void inp_instruction(int32_t& a, int32_t value)
{
	a = value;
}
void add_instruction(int32_t& a, int32_t b)
{
	a += b;
}

void mul_instruction(int32_t& a, int32_t b)
{
	a *= b;
}

void div_instruction(int32_t& a, int32_t b)
{
	a = std::floor(static_cast<float>(a) / b);
}

void mod_instruction(int32_t& a, int32_t b)
{
	a %= b;
}

void eql_instruction(int32_t& a, int32_t b)
{
	if(a == b) { a = 1; } else { a = 0; }
}
