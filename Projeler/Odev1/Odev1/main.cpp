#define _USE_MATH_DEFINES


#include <filesystem>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

#include "Bullet.h"
#include "Cannon.h"
#include "Utils.h"

constexpr auto win_width = 480;
constexpr auto win_height = 640;

int main()
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

	// Mekanik
	float angle = 270.f;
	float distance = 120.f;

	sf::Vector2f aimDir;
	sf::Vector2f aimDirNorm;

	// Bullet
	Bullet b1;
	std::vector<Bullet> bullets;

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
				b1.shape.setPosition(cannon.circle_center);
				b1.currentVelocity = aimDirNorm * b1.maxSpeed;

				bullets.emplace_back(b1);
			}
		}

		std::cout << angle << std::endl;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && angle < 340)
			angle += 2.f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && angle > 200)
			angle -= 2.f;

		angle = fmod(angle, 360.f);
		if (angle > 360) angle -= 360;

		orbiting.setPosition(cannon.shape.getPosition().x + cos(angle * M_PI / 180) * distance, cannon.shape.getPosition().y + sin(angle * M_PI / 180) * distance);
		line.setRotation(angle);
		aimDir = orbiting.getPosition() - cannon.shape.getPosition();
		aimDirNorm = utils::normalize(aimDir);


		for (auto& bullet : bullets)
		{
			bullet.shape.move(bullet.currentVelocity);
			sf::Vector2f new_position = bullet.shape.getPosition();
			float bullet_radius = bullet.shape.getRadius();
			if (new_position.x - bullet_radius < 0)
			{
				bullet.currentVelocity.x *= -1;
			}
			else if (new_position.x + bullet_radius >= win_width)
			{
				bullet.currentVelocity.x *= -1;
			}
		}

		// Draw
		window.clear();

		window.draw(cannon.shape);
		window.draw(orbiting);
		window.draw(line);

		for (auto& bullet : bullets)
		{
			window.draw(bullet.shape);
		}

		window.display();
	}
	return 0;
}