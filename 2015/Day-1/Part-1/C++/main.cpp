#include "../../../../Utils/Util.h"

int main(void)
{
	auto data = load_file("../../Data/data.txt");

	int32_t floor = 0;
	for(size_t i = 0; i < data.size(); ++i)
	{
		if(data[i] == '(') floor += 1;
		else if(data[i] == ')') floor -= 1;
	}

	PRINT(floor);

	return 0;
}
