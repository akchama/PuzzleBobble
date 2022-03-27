#pragma once

#include <SFML/Graphics.hpp>

/**
 * Projectile
 */
class Bullet
{
public:
	sf::CircleShape		shape;
	sf::Vector2f		currentVelocity;
	float				maxSpeed;

	Bullet(float radius = 20.0f);
};