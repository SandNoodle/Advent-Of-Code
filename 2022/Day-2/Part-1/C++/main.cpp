#include "../../../../Utils/Util.h"

#include <unordered_map>

int main(void)
{
	auto file_data = load_file("../../Data/data.txt");
	auto lines = create_vector(file_data, '\n', false);

	const std::unordered_map<std::string, int32_t> lookup = {
		{"A Y", 6 + 2}, {"B Z", 6 + 3}, {"C X", 6 + 1}, // Win
		{"A X", 3 + 1}, {"B Y", 3 + 2}, {"C Z", 3 + 3}, // Draw
		{"A Z", 0 + 3}, {"B X", 0 + 1}, {"C Y", 0 + 2}  // Lose
	};

	Timer timer;
	int32_t score = 0;
	std::ranges::for_each(lines, [&score, lookup]
			(const auto& l){score += lookup.at(l);});
	PRINT(score);

	return 0;
}
