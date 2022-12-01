#include "../../../../Utils/Util.h"

struct Box
{
	int32_t l;
	int32_t w;
	int32_t h;

	constexpr Box(int32_t l, int32_t w, int32_t h)
		: l(l), w(w), h(h) { }

	constexpr int32_t surface_area() const
		{ return (2 * l * w) + (2 * w * h) + (2 * h * l); };

	constexpr int32_t smallest_side_area() const
	{
		int32_t a = w * l;
		int32_t b = w * h;
		int32_t c = h * l;

		return std::min(a, std::min(b, c));
	}
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
		sum += b.surface_area() + b.smallest_side_area();});

	PRINT(sum);

	return 0;
}
