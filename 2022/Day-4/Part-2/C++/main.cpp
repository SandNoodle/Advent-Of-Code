#include "../../../../Utils/Util.h"

int main(void)
{
	auto file_data = load_file("../../Data/data.txt");
	auto lines = create_vector(file_data, '\n', false);

	Timer timer;
	int32_t overlaps = 0;
	std::ranges::for_each(lines, [&overlaps](const auto& l)
	{
		auto pair = create_vector(l, ',', false);
		auto first = create_vector(pair[0], '-', false);
		auto second = create_vector(pair[1], '-', false);
		if(is_range_overlap(
					to_number(first[0]), to_number(first[1]),
					to_number(second[0]), to_number(second[1])))
			overlaps++;
	});

	PRINT(overlaps);

	return 0;
}
