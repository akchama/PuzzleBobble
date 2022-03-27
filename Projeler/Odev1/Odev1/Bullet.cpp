#include "Bullet.h"
#include <SFML/Graphics.hpp>

Bullet::Bullet(float radius) : currentVelocity(0.0f, 0.0f), maxSpeed(8.0f)
{
	this->shape.setRadius(radius);
	this->shape.setOrigin(radius, radius);
	this->shape.setFillColor(sf::Color::Red);
}