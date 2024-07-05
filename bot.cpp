#include "bot.h"
#include "game.h"

#define MAXVALUE 9999
#define MINVALUE -9999
#define MAXDEPTH 8

namespace Bot {
	static int __action(const int& nrows, const int& ncols, std::vector<std::vector<Game::OccupiedBy>>& playfield, unsigned depth, int alfa, int beta, Game::OccupiedBy current_player) {
		if (depth == MAXDEPTH) {
			return evaluate(nrows, ncols, playfield);
		}

		int curr_eval = evaluate(nrows, ncols, playfield);
		if (curr_eval == MAXVALUE || curr_eval == MINVALUE) {
			return curr_eval;
		}

		if (current_player == Game::OccupiedBy::P1) {
			for (int col = 0; col < ncols; col++) {
				if (playfield[0][col] != Game::OccupiedBy::EMPTY) continue;
				drop(col, nrows, current_player, playfield);
				int result = __action(nrows, ncols, playfield, depth + 1, alfa, beta, Game::P2);
				alfa = std::max(alfa, result);
				undrop(col, nrows, playfield);
				//if (min <= best) return best;
				if (beta <= alfa) break;
			}
			return alfa;
		}
		else {
			for (int col = 0; col < ncols; col++) {
				if (playfield[0][col] != Game::OccupiedBy::EMPTY) continue;
				drop(col, nrows, current_player, playfield);
				int result = __action(nrows, ncols, playfield, depth + 1, alfa, beta, Game::P1);
				beta = std::min(beta, result);
				undrop(col, nrows, playfield);
				//if (min <= best) return best;
				if (beta <= alfa) break;
			}
			return beta;
		}
	}

	int action(const int& nrows, const int& ncols, std::vector<std::vector<Game::OccupiedBy>>& playfield) {
		int best_col = 0;
		int best = MAXVALUE;

		for (int col = 0; col < ncols; col++) {
			if (playfield[0][col] != Game::OccupiedBy::EMPTY) continue;

			drop(col, nrows, Game::P2, playfield);
			int result = __action(nrows, ncols, playfield, 1, MINVALUE, best, Game::OccupiedBy::P1);
			if (result < best) {
				best = result;
				best_col = col;
			}
			undrop(col, nrows, playfield);
		}

		return best_col;
	}

	static int evaluate(const int& nrows, const int& ncols, std::vector<std::vector<Game::OccupiedBy>>& playfield) {
		int best1 = 0;
		int best2 = 0;

		for (auto player : { Game::OccupiedBy::P1, Game::OccupiedBy::P2 }) {
			int best = 0;

			// horizontal
			for (int i = 0; i < nrows; i++) {
				for (int j = 0; j < ncols - 3; j++) {
					int k;
					for (k = 0; k < 4; k++) {
						if (playfield[i][j + k] != player) break;
					}
					best = std::max(best, k);
				}
			}

			// vertical
			for (int i = 0; i < nrows - 3; i++) {
				for (int j = 0; j < ncols; j++) {
					int k;
					for (k = 0; k < 4; k++) {
						if (playfield[i + k][j] != player) break;
					}
					best = std::max(best, k);
				}
			}

			// diagonal to right
			for (int i = 0; i < nrows - 3; i++) {
				for (int j = 0; j < ncols - 3; j++) {
					int k;
					for (k = 0; k < 4; k++) {
						if (playfield[i + k][j + k] != player) break;
					}
					best = std::max(best, k);
				}
			}

			// diagonal to left
			for (int i = 0; i < nrows - 3; i++) {
				for (int j = 3; j < ncols; j++) {
					int k;
					for (k = 0; k < 4; k++) {
						if (playfield[i + k][j - k] != player) break;
					}
					best = std::max(best, k);
				}
			}

			if (player == Game::P1) {
				best1 = best;
			}
			else {
				best2 = best;
			}
		}

		if (best1 == 4) {
			return MAXVALUE;
		}
		else if (best2 == 4) {
			return MINVALUE;
		}
		return best1 - best2;
	}

	static void drop(const int& col, const int& nrows, const Game::OccupiedBy& value, std::vector<std::vector<Game::OccupiedBy>>& playfield) {
		int row;
		for (row = 0; row < nrows-1; row++) {
			if (playfield[row+1][col] != Game::OccupiedBy::EMPTY) {
				break;
			}
		}

		playfield[row][col] = value;
	}

	static void undrop(const int& col, const int& nrows, std::vector<std::vector<Game::OccupiedBy>>& playfield) {
		int row;
		for (row = 0; row < nrows; row++) {
			if (playfield[row][col] != Game::OccupiedBy::EMPTY) {
				break;
			}
		}

		playfield[row][col] = Game::OccupiedBy::EMPTY;
	}
}