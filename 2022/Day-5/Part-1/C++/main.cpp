#include "../../../../Utils/Util.h"

#include <array>
#include <stack>

int main(void)
{
	// ------------------------------------------------------------------------
	auto file_data = load_file("../../Data/data.txt");
	auto lines = create_vector(file_data, '\n', true);

	auto position_it = std::find(lines.begin(), lines.end(), "");
	auto index = position_it - lines.begin();

	auto stack_lines = std::vector<std::string>(lines.begin(), lines.begin() + index);
	auto instruction_lines = std::vector<std::string>(lines.begin() + index + 1, lines.end());

	auto line_size = stack_lines[0].size();
	auto stacks_count = (line_size + 1) / 4;
	std::vector<std::stack<char>> stacks;
	stacks.reserve(stacks_count);

	for(size_t column_index = 1; column_index < line_size; column_index += 4)
	{
		std::stack<char> stack;
		auto row_index = stack_lines.size() - 2;
		while(row_index >= 1)
		{
			auto c = stack_lines[row_index][column_index];
			if(c == ' ') break;

			stack.push(c);
			--row_index;
		}
		char c = stack_lines[0][column_index];
		if(c != ' ') stack.push(c);

		stacks.push_back(stack);
	}

	std::vector<std::vector<int32_t>> instructions;
	std::ranges::for_each(instruction_lines, [&instructions](const auto& l)
		{
			auto string_range = create_vector(l, "[^0-9]+");
			auto range = convert_to_int_vector(string_range);
			instructions.push_back(range);
		});

	// ------------------------------------------------------------------------

	Timer timer;
	const auto rearrange_stacks_function = [&stacks](const auto& instruction)
	{
		for(size_t i = 0; i < instruction[0]; ++i)
		{
			auto from_index = instruction[1] - 1;
			auto to_index = instruction[2] - 1;
			stacks[to_index].push(stacks[from_index].top());
			stacks[from_index].pop();
		}
	};
	std::ranges::for_each(instructions, rearrange_stacks_function);
	auto result = std::string();
	std::ranges::for_each(stacks, [&result](const auto& s){result += s.top();});

	PRINT(result);

	// ------------------------------------------------------------------------

	return 0;
}
