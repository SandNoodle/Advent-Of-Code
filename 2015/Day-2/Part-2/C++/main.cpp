#include "../../../../Utils/Util.h"

struct Box
{
	int32_t l;
	int32_t w;
	int32_t h;

	constexpr Box(int32_t l, int32_t w, int32_t h)
		: l(l), w(w), h(h) { }

	constexpr int32_t shortest_distance() const
	{
		int32_t array[] = { l, w, h };
		std::sort(std::begin(array), std::end(array));

		return array[0] + array[0] + array[1] + array[1];
	};

	constexpr int32_t volume() const
	{
		return l * w * h;
	};
};

int main(void)
{
	auto file_data = load_file("../../Data/data.txt");
	auto lines = create_vector<std::string>(file_data, '\n', false);

	Timer timer;
	std::vector<Box> boxes;
	boxes.reserve(lines.size());
	for(const auto& l : lines)
	{
		auto delimited = create_vector<std::string>(l, 'x', false);
		boxes.push_back(Box(
					std::atoi(delimited[0].c_str()),
					std::atoi(delimited[1].c_str()),
					std::atoi(delimited[2].c_str())));
	}
	int32_t sum = 0;
	std::ranges::for_each(boxes, [&sum](const auto& b){
		sum += b.volume() + b.shortest_distance();});

	PRINT(sum);

	return 0;
}
