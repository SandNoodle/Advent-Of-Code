#include "../../../../Utils/Util.h"

int main(void)
{
	auto file_data = load_file("../../Data/data.txt");
	auto lines = create_vector(file_data, '\n', false);

	Timer timer;
	uint32_t sum = 0;
	std::ranges::for_each(lines, [&sum](const auto& l){
			const auto half_size = l.size() / 2;
			auto lower = l.substr(0, half_size);
			auto upper = l.substr(half_size);
			char common_item = std::invoke([&lower, &upper](){
					std::sort(lower.begin(), lower.end());
					std::sort(upper.begin(), upper.end());
					std::string intersection;
					std::set_intersection( lower.begin(), lower.end(),
							upper.begin(), upper.end(),
							std::back_inserter(intersection));
					return intersection[0];
				});
			if(common_item >= 'a' && common_item <= 'z') sum += common_item - 96;
			if(common_item >= 'A' && common_item <= 'Z') sum += common_item - 38;
		});
	PRINT(sum);

	return 0;
}
