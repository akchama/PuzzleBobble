#pragma once

#include <SFML/Graphics.hpp>

/**
 * Projectile
 */
class Bobble
{
public:
	sf::CircleShape		shape;
	sf::Vector2f		current_velocity;
	sf::Color			color;
	sf::Color			color_array[5];
	float				max_speed;
	float				radius;
	bool				is_moving;
	bool				connected;
	bool				matching;
	std::vector<Bobble> touching_bobbles;
	int					id;

	void set_position(sf::Vector2f);
	explicit Bobble(std::vector<Bobble>& bobbles, float radius = 27.0f);
	void stop();
	sf::Color get_random_color() const;
	void set_matching(bool m);

private:
	std::vector<Bobble> bobbles_;
};