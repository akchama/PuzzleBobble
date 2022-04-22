#pragma once
#define _USE_MATH_DEFINES


#include "GameManager.h"

#include <filesystem>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <random>

#include "Bobble.h"
#include "Cannon.h"
#include "Grid.h"
#include "Utils.h"

constexpr auto win_width = 440;
constexpr auto win_height = 640;

void GameManager::shoot_bobble(Cannon& cannon, sf::Vector2f aim_dir_norm, Bobble& b1, sf::Color next_color, int& new_id)
{
	b1.shape.setPosition(cannon.circle_center);
	b1.current_velocity = aim_dir_norm * b1.max_speed;
	b1.shape.setFillColor(next_color);
	b1.is_moving = true;
	b1.id = new_id;
	new_id++;
}


void GameManager::burst_matching_bubbles(Bobble& bobble, bobble& target)
{
	sf::Vector2f dump_pos(-100.f, -100.f);
	auto distance = sqrt(pow(target.shape.getPosition().x - bobble.shape.getPosition().x, 2)
		+ pow(target.shape.getPosition().y - bobble.shape.getPosition().y, 2));

	if (distance < 60 && target.shape.getFillColor() == bobble.shape.getFillColor() && !target.matching) 
	{
		std::cout << "Matching!!!";
		bobble.matching = true;
		target.matching = true;
		bobble.set_position(dump_pos);
		target.set_position(dump_pos);
		burst_matching_bubbles(bobble, target);
	}
}

void GameManager::run()
{
	sf::RenderWindow window(sf::VideoMode(win_width, win_height), "Puzzle Bobble");
	window.setFramerateLimit(144);
	window.setKeyRepeatEnabled(false);

	Cannon cannon(win_width, win_height);

	// Invisible shape to get direction
	float orbitingRadius = 0.f;
	auto orbiting = sf::CircleShape(orbitingRadius);
	orbiting.setOrigin(orbitingRadius, orbitingRadius);
	orbiting.setPosition(sf::Vector2f(win_width / 2.f, win_height / 2.f));

	float line_length = 100.f;
	float line_thickness = 15.f;
	auto line = sf::RectangleShape(sf::Vector2f(line_length, line_thickness));
	line.setOrigin(line.getPosition().x, line.getPosition().y + line.getSize().y / 2);
	line.setPosition(cannon.shape.getPosition());
	line.setFillColor(sf::Color::Yellow);

	sf::Font font;
	if (!font.loadFromFile("fonts/ARCADE_R.ttf"))
	{
		std::cout << "font not loaded" << std::endl;
	}

	sf::Clock clock;

	// UI
	sf::Text text;
	// select the font
	text.setFont(font); // font is a sf::Font
	// set the string to display
	text.setString("SIRADAKI\nRENK");
	// set the character size
	text.setCharacterSize(14); // in pixels, not points!
	// set the color
	text.setFillColor(sf::Color::Red);
	// set the text style
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	text.setPosition(30, 500);


	// Mekanik
	float angle = 270.f;
	float distance = 120.f;

	sf::Vector2f aim_dir;
	sf::Vector2f aim_dir_norm;

	// Bobble
	std::vector<Bobble> bobbles;
	Bobble b1(bobbles);
	sf::Color next_color = b1.get_random_color();

	Grid Grid;
	Bobble next_color_bobble(bobbles);
	next_color_bobble.shape.setFillColor(next_color);
	next_color_bobble.shape.setPosition(50, 575);

	int new_id = 0;

	while (window.isOpen())
	{
		sf::Event event{};
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
			{
				shoot_bobble(cannon, aim_dir_norm, b1, next_color, new_id);
				bobbles.emplace_back(b1);
				next_color = b1.get_random_color(); // Sýradaki renk
				next_color_bobble.shape.setFillColor(next_color); // Gösterge balonu
			}
		}

		if (clock.getElapsedTime().asSeconds() > 1 / 144.f)
		{
			for (auto& bobble : bobbles)
			{
				for (auto& target : bobbles)
				{
					if (bobble.id != target.id)
					{
						auto distance = sqrt(pow(target.shape.getPosition().x - bobble.shape.getPosition().x, 2)
							+ pow(target.shape.getPosition().y - bobble.shape.getPosition().y, 2));

						if (distance < 48)
						{
							bobble.stop();
						}

						if (!bobble.is_moving)
						{
							burst_matching_bubbles(bobble, target);
						}
					}
				}
			}
			clock.restart();
		}


		// Açý ayarlamasý
		utils::handle_angle(angle, 1.f);

		orbiting.setPosition(cannon.shape.getPosition().x + cos(angle * M_PI / 180) * distance, cannon.shape.getPosition().y + sin(angle * M_PI / 180) * distance);
		line.setRotation(angle);
		aim_dir = orbiting.getPosition() - cannon.shape.getPosition();
		aim_dir_norm = utils::normalize(aim_dir);

		for (auto& bobble : bobbles)
		{
			bobble.shape.move(bobble.current_velocity);
			sf::Vector2f new_position = bobble.shape.getPosition();
			float bobble_radius = bobble.shape.getRadius();
			if (new_position.x - bobble_radius < 0)
			{
				bobble.current_velocity.x *= -1;
			}
			else if (new_position.x + bobble_radius >= win_width)
			{
				bobble.current_velocity.x *= -1;
			}
			else if (new_position.y - bobble_radius < 0)
			{
				bobble.stop();
			}
		}

		grid.align_bobbles(bobbles);

		// Draw
		window.clear();

		window.draw(cannon.shape);
		window.draw(orbiting);
		window.draw(line);
		window.draw(text);
		window.draw(next_color_bobble.shape);

		for (auto& bobble : bobbles)
		{
			window.draw(bobble.shape);
		}

		window.display();
	}
}
