#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>

namespace utils
{
	[[nodiscard]] sf::Vector2f normalize(const sf::Vector2f& source);
	int get_index(std::vector<int> v, float k);
	void handle_angle(float&, float);
};

