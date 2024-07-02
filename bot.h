#pragma once
#include <vector>
#include "game.h"

namespace Bot {
	int action(const int& nrows, const int& ncols, std::vector<std::vector<Game::OccupiedBy>>& playfield);
}