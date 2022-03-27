#include "Cannon.h"
#include <SFML/Graphics.hpp>


Cannon::Cannon(float win_width, float win_height)
	: platform_y(win_height - 50.f)
{
	this->shape.setOrigin(circle_radius, circle_radius);
	this->shape.setPosition(sf::Vector2f(win_width / 2.f, platform_y));
	this->circle_center = shape.getPosition();
}