#include "game.h"
#include "olcPixelGameEngine.h"
#include "window.h"
#include "animation.h"
#include <vector>

Game::Game(int nrows, int ncols, Window* canvas) : nrows(nrows), ncols(ncols), playfield(nrows, std::vector<OccupiedBy>(ncols, OccupiedBy::EMPTY)) {
	this->canvas = canvas;
}

void Game::draw_board() {
	canvas->SetPixelMode(olc::Pixel::Mode::NORMAL);
	canvas->DrawRect(olc::vi2d(pad1x, pad1y + draw_dy), olc::vi2d(draw_space1x, draw_space1y - draw_dy), olc::WHITE);

	for (int i = 0; i < ncols; i++) {
		for (int j = 0; j < nrows; j++) {
			float x = i * draw_dx + pad1x;
			float y = (j + 1) * draw_dy + pad1y;
			canvas->FillCircle(olc::vi2d(x + draw_dx / 2, y + draw_dy / 2), draw_radius, token_colors[playfield[j][i]]);
		}
	}
}

void Game::handle_gameover_draw() {
	draw_board();
	canvas->DrawString(olc::vi2d(0, 20), token_names[winner] + " WINS!!!", token_colors[winner], 8U);
	
}

void Game::handle_gampeplay_draw() {
	draw_board();

	float r = std::min(draw_dx, draw_dy) / 2 * 0.9;

	if (lin_anim == nullptr) {
		int col = get_selected_col();
		canvas->FillCircle(olc::vi2d(col * draw_dx + draw_dx / 2 + pad1x, pad1y + draw_dy / 2), r, token_colors[current_player]);
	}
	else {
		float stry = pad1y + draw_dy;
		canvas->SetPixelMode([&stry](const int x, const int y, const olc::Pixel& todraw, const olc::Pixel& drawn)->olc::Pixel {
			if (drawn.r == 0 && drawn.g == 0 && drawn.b == 0 && y > stry) {
				return drawn;
			}
			return todraw;
		});
		//canvas->SetPixelMode(olc::Pixel::Mode::ALPHA);
		//std::cout << lin_anim->get() << ' ' << lin_anim->speed << '\n';
		canvas->FillCircle(olc::vi2d(lin_anim->data.x, lin_anim->get()), r, token_colors[current_player]);
		//std::cout << lin_anim->data << ' ' << lin_anim->get() << '\n';
	}
}

void Game::draw() {
	if (!gameover) {
		handle_gampeplay_draw();
	}
	else {
		handle_gameover_draw();
	}
}


void Game::handle_gameplay_update(float fElapsedTime) {
	if (lin_anim == nullptr) {
		if (canvas->GetMouse(olc::Mouse::LEFT).bPressed) {
			int col = get_selected_col();
			int i;
			for (i = 0; i < nrows; i++) {
				if (playfield[i][col] != OccupiedBy::EMPTY) {
					break;
				}
			}
			if (i > 0) {
				DropInfo dp = { col * draw_dx + pad1x + draw_dx / 2 , col, i - 1 };
				lin_anim = new LinearAnimation<DropInfo>(pad1y + draw_dy / 2, i * draw_dy + pad1y + draw_dy / 2, animation_speed, dp);
			}
		}
	}
	else {
		if (lin_anim->finished) {
			//std::cout << lin_anim->end << ' '<< lin_anim->progress << "END\n";
			playfield[lin_anim->data.row][lin_anim->data.col] = current_player;
			current_player = current_player == OccupiedBy::P1 ? OccupiedBy::P2 : OccupiedBy::P1;
			delete lin_anim;
			lin_anim = nullptr;

			winner = check_win();
			if (winner != OccupiedBy::EMPTY) {
				std::cout << winner << " WINS!!";
				gameover = true;
			}

		}
		else {
			lin_anim->update(fElapsedTime);
		}
	}
}

void Game::update(float fElapsedTime) {
	draw_space1y = this->canvas->ScreenHeight() - pad1y * 2;
	draw_space1x = this->canvas->ScreenWidth() - pad1x * 2;
	draw_dy = draw_space1y / (nrows + 1);
	draw_dx = draw_space1x / ncols;
	draw_radius = std::min(draw_dx, draw_dy) * 0.75 / 2;
	//std::cout << draw_dx << ' ' << draw_dy << ' ' << draw_radius << '\n';

	if (!gameover) {
		handle_gameplay_update(fElapsedTime);
	}

}

int Game::get_selected_col() {
	int col = (canvas->GetMouseX() - pad1x) / draw_dx;
	col = std::max(std::min(ncols - 1, col), 0);
	return col;
}

Game::OccupiedBy Game::check_win() {
	//std::array<std::array<bool, ncols>, nrows> horizontal;
	//bool nigg[cols][rows] = {};
	
	for (auto player : { OccupiedBy::P1, OccupiedBy::P2 }) {
		// horizontal
		for (int i = 0; i < nrows; i++) {
			for (int j = 0; j < ncols-3; j++) {
				for (int k = 0; k < 4; k++) {
					if (playfield[i][j + k] != player) goto Unsuccesful;
				}
				return player;
			Unsuccesful:;
			}
		}

		// vertical
		for (int i = 0; i < nrows-3; i++) {
			for (int j = 0; j < ncols; j++) {
				for (int k = 0; k < 4; k++) {
					if (playfield[i+k][j] != player) goto Unsuccesful2;
				}
				return player;
			Unsuccesful2:;
			}
		}

		// diagonal to right
		for (int i = 0; i < nrows-3; i++) {
			for (int j = 0; j < ncols - 3; j++) {
				for (int k = 0; k < 4; k++) {
					if (playfield[i+k][j + k] != player) goto Unsuccesful3;
				}
				return player;
			Unsuccesful3:;
			}
		}

		// diagonal to left
		for (int i = 0; i < nrows-3; i++) {
			for (int j = 3; j < ncols; j++) {
				for (int k = 0; k < 4; k++) {
					if (playfield[i + k][j - k] != player) goto Unsuccesful4;
				}
				return player;
			Unsuccesful4:;
			}
		}
	}

	return OccupiedBy::EMPTY;
}

//void Game::drop(const int& col) {
//	int i;
//	for (i = 0; i < nrows; i++) {
//		if (playfield[i][col] != OccupiedBy::EMPTY) {
//			break;
//		}
//	}
//	DropInfo dp = { col * draw_dx + pad1x + draw_dx / 2 , col, i-1 };
//	lin_anim = new LinearAnimation<DropInfo>(pad1y + draw_dy / 2, i * draw_dy + pad1y + draw_dy / 2, 2, dp);
//	std::cout << lin_anim->speed << "spe\n";
//	//std::cout << i << "i\n";
//	//std::cout << lin_anim->end << "En2\n";
//}