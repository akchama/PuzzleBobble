#pragma once

#include <SFML/Graphics.hpp>

class Cannon
{
public:
	float			platform_y;
	float			circle_radius = 50.f;
	sf::Vector2f	circle_center;
	sf::CircleShape	shape = sf::CircleShape(circle_radius);

	Cannon(float win_width, float win_height);
};

