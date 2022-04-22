#pragma once
#include "Bobble.h"
#include "Cannon.h"
#include "Grid.h"

class GameManager
{
public:
	void burst_matching_bubbles(Bobble&, Bobble&);
	void run();
	void find_matching_bobbles(Bobble& value,
		std::vector<Bobble>& bobbles);
	void shoot_bobble(Cannon& cannon, sf::Vector2f aim_dir_norm, Bobble& b1, sf::Color next_color, int& new_id);
	void align_bobbles(std::vector<Bobble> bobbles, Grid grid);
};

