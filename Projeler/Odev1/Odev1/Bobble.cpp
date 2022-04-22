#include "Bobble.h"

#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>

void Bobble::set_position(sf::Vector2f pos)
{
	this->shape.setPosition(pos);
}

Bobble::Bobble(std::vector<Bobble>& bobbles, const float radius)
	: current_velocity(0.0f, 0.0f),
		color(this->shape.getFillColor()),
		max_speed(8.0f),
		radius(radius),
		is_moving(false),
		touching_bobbles({}),
		id(0),
		bobbles_(bobbles)
{
	color_array[0] = sf::Color::Cyan;
	color_array[1] = sf::Color::Blue;
	color_array[2] = sf::Color::Green;
	color_array[3] = sf::Color::Red;
	color_array[4] = sf::Color::Yellow;

	this->matching = false;
	this->shape.setRadius(radius);
	this->shape.setOrigin(radius, radius);
}

void Bobble::stop()
{
	this->current_velocity.x = 0;
	this->current_velocity.y = 0;
	this->is_moving = false;
}

sf::Color Bobble::get_random_color() const
{
	std::mt19937 rng(std::random_device{}());
	const std::uniform_int_distribution<> dist(0, 4);
	const auto random_number = dist(rng);

	return color_array[random_number];
}

void Bobble::set_matching(bool m)
{
	this->matching = m;
}