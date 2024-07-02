#pragma once
#include <vector>
#include "game.h"

namespace Bot {
	static int __action(const int& nrows, const int& ncols, std::vector<std::vector<Game::OccupiedBy>>& playfield, unsigned depth, int min, int max, Game::OccupiedBy current);
	int action(const int& nrows, const int& ncols, std::vector<std::vector<Game::OccupiedBy>>& playfield);
	static int evaluate(const int& nrows, const int& ncols, std::vector<std::vector<Game::OccupiedBy>>& playfield);
	static void drop(const int& col, const int& nrows, const Game::OccupiedBy& value, std::vector<std::vector<Game::OccupiedBy>>& playfield);
	static void undrop(const int& col, const int& nrows, std::vector<std::vector<Game::OccupiedBy>>& playfield);
}