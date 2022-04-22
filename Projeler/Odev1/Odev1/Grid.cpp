#include "Grid.h"

#include <algorithm>
#include <iostream>

#include "Bobble.h"
#include "Utils.h"


Grid::Grid()
	: top_row_eight(true)
{
	constexpr int offset = 27;
	this->x_coordinates = {
				{
					0 + offset,
					55 + offset,
					110 + offset,
					165 + offset,
					220 + offset,
					275 + offset,
					330 + offset,
					385 + offset
				},
				{
					0,
					55,
					110,
					165,
					220,
					275,
					330,
					385
				}
	};

	for (int i = 0; i < 10; i ++)
	{
		y_coordinates.emplace_back(i * 48 + 27);
	}
}

float Grid::closest_coordinate(std::vector<int> const v, float target)
{
	auto i = min_element(begin(v), end(v), [=](int x, int y)
		{
			return abs(x - target) < abs(y - target);
		});

	return v[distance(begin(v), i)];
}

float Grid::get_nearest(float x, float y, float target) {
	if (target - x >= y - target)
		return y;
	else
		return x;
}

void Grid::align_bobbles(std::vector<Bobble> &bobbles)
{
	for (auto& bobble : bobbles)
	{
		if (bobble.is_moving == false && !bobble.matching)
		{
			float player_bobble_y = this->closest_coordinate(this->y_coordinates, bobble.shape.getPosition().y);
			// Y koordinatlarýnda hizala
			bobble.shape.setPosition(bobble.shape.getPosition().x, player_bobble_y);

			if (this->top_row_eight)
			{
				if (utils::get_index(this->y_coordinates, player_bobble_y) % 2)
				{
					bobble.shape.setPosition(
						this->closest_coordinate(this->x_coordinates[1], bobble.shape.getPosition().x),
						bobble.shape.getPosition().y);
				}
				else
				{
					bobble.shape.setPosition(
						this->closest_coordinate(this->x_coordinates[0], bobble.shape.getPosition().x),
						bobble.shape.getPosition().y);
				}
			}
		}
	}
}