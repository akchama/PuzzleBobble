#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wfloat-equal"

#include "Utils.h"
#include <cmath>
#include <SFML/System/Vector2.hpp>

namespace utils
{
	sf::Vector2f normalize(const sf::Vector2f& source)
	{
		if (const float length = sqrt((source.x * source.x) + (source.y * source.y)); length != 0)
			return { source.x / length, source.y / length };
		return source;
	}
}

#pragma clang diagnostic pop