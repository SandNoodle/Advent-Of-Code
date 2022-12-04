#include "../../../../Utils/Util.h"

int main(void)
{
	auto file_data = load_file("../../Data/data.txt");
	auto lines = create_vector(file_data, '\n', false);
	std::vector<std::vector<int32_t>> groups;
	groups.reserve(lines.size());
	std::ranges::for_each(lines, [&groups](const auto& l)
	{
		std::vector<std::string> string_range = create_vector(l, "[^\\d]+");
		std::vector<int32_t> range = convert_to_int_vector(string_range);
		groups.push_back(range);
	});

	Timer timer;
	int32_t overlaps = 0;
	std::ranges::for_each(groups, [&overlaps](const auto& g)
		{ if(is_range_fully_overlap(g[0], g[1], g[2], g[3])) overlaps++; });

	PRINT(overlaps);

	return 0;
}
