#include "../../../../Utils/Util.h"

int main(void)
{
	auto file_data = load_file("../../Data/data.txt");
	auto lines = create_vector(file_data, '\n', false);
	std::vector<std::vector<std::string>> groups;
	for(auto i = 0; i < lines.size(); i+=3)
	{
		groups.insert(groups.end(), { lines[i], lines[i+1], lines[i+2] });
	}

	Timer timer;
	uint32_t sum = 0;
	std::ranges::for_each(groups, [&sum](const auto& g){
			auto first = g[0]; auto second = g[1]; auto third = g[2];
			char common_item = std::invoke([&](){
					std::sort(first.begin(), first.end());
					std::sort(second.begin(), second.end());
					std::sort(third.begin(), third.end());
					std::string intersection_a, intersection_b;
					std::set_intersection( first.begin(), first.end(),
							second.begin(), second.end(),
							std::back_inserter(intersection_a));
					std::set_intersection( third.begin(), third.end(),
							intersection_a.begin(), intersection_a.end(),
							std::back_inserter(intersection_b));
					return intersection_b[0];
				});
			if(common_item >= 'a' && common_item <= 'z') sum += common_item - 96;
			if(common_item >= 'A' && common_item <= 'Z') sum += common_item - 38;
		});

	PRINT(sum);

	return 0;
}
