#include "../../include/utils/math.hpp"
#include <cstdlib>

namespace Utils {
	float random(float min, float max)
	{
		return min + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX) / (max - min));
	}

	int random(int min, int max)
	{
		return min + static_cast<int>(std::rand()) / (static_cast<int>(RAND_MAX) / (max - min));
	}
}
