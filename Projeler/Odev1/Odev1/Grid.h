#pragma once
#include <vector>

#include "Bobble.h"


class Grid
{
public:
	std::vector<int>				y_coordinates;
	std::vector<std::vector<int>>	x_coordinates;
	bool							top_row_eight;

	Grid();
	void align_bobbles(std::vector<Bobble>&);
	float closest_coordinate(std::vector<int> const v, float target);
	float get_nearest(float x, float y, float target);
};
