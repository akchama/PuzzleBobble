#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wfloat-equal"

#include "Utils.h"
#include <cmath>
#include <iostream>
#include <ostream>
#include <vector>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace utils
{
	sf::Vector2f normalize(const sf::Vector2f& source)
	{
		if (const float length = sqrt((source.x * source.x) + (source.y * source.y)); length != 0)
			return { source.x / length, source.y / length };
		return source;
	}

	// Function to print the
	// index of an element
	int get_index(std::vector<int> v, const float k)
	{
		// If element was found
		if (const auto it = std::find(v.begin(), v.end(), k); it != v.end())
		{
			// calculating the index
			// of K
			const int index = it - v.begin();
			return index;
		}
		return -1;
	}

	void handle_angle(float& angle, const float angle_change_speed)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && angle < 340)
		{
			angle += angle_change_speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && angle > 200)
		{
			angle -= angle_change_speed;
		}

		angle = fmod(angle, 360.f);
		if (angle > 360) angle -= 360;
	}
}

#pragma clang diagnostic pop