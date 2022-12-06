#include "../../../../Utils/Util.h"

int main(void)
{
	auto file_data = load_file("../../Data/data.txt");
	// Data has only 1 line.
	auto packet = create_vector(file_data, '\n', true)[0];

	const auto is_slice_a_header = [](auto& slice)
	{
		std::sort(slice.begin(), slice.end());

		for(size_t i = 0; i < slice.size() - 1; ++i)
			if(slice[i] == slice[i + 1])
				return false;
		return true;
	};

	Timer timer;
	constexpr auto slice_size = 4;
	auto last_index = 0;
	for(size_t i = 0; i < packet.size(); ++i)
	{
		const auto slice_start = packet.begin() + i;
		auto slice = std::string(slice_start, slice_start + slice_size);
		if(is_slice_a_header(slice))
		{
			last_index = i + slice_size;
			break;
		}
	}

	PRINT("INDEX: " << last_index);

	return 0;
}
