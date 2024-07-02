#pragma once
#include <vector>
#include "olcPixelGameEngine.h"

class Window;
template <typename T> class QuadraticAnimation;
class Button;

struct DropInfo {
	int x;
	int col;
	int row;
};

class Game {
public: 
	enum OccupiedBy {
		EMPTY,
		P1,
		P2
	};

	const olc::Pixel token_colors[3] = { olc::WHITE, olc::RED, olc::BLUE };
	const std::string token_names[3] = { "DRAW", "RED", "BLUE" };

private:
	void draw_choice(const int& col);
	void drop(const int& col);
	int get_selected_col();
	OccupiedBy check_win();
	QuadraticAnimation<DropInfo>* lin_anim = nullptr;
	OccupiedBy current_player = OccupiedBy::P1;
	void handle_gameplay_update(float fElapsedTime);
	void handle_gampeplay_draw();
	void handle_gameover_draw();
	void draw_board();

	float draw_space1y;
	float draw_space1x;
	float draw_dy;
	float draw_dx;
	float draw_radius;

	static const int animation_speed = 3000;

	bool gameover = false;
	bool pve = true;
	OccupiedBy winner = OccupiedBy::EMPTY;

	Button* play_again_btn = nullptr;
	Button* menu_btn = nullptr;

public:
	bool killme = false;

	const int nrows;
	const int ncols;
	Window *canvas;


	static const int pad1x = 10;
	static const int pad1y = 10;
	//static const int pad2x = 10;
	//static const int pad2y = 10;
	//static const int gapx = 5;
	//static const int gapy = 5;
	//static const int dropdiff = 6;



	std::vector<std::vector<OccupiedBy>> playfield;

	Game(int nrows, int ncols, Window* canvas);
	void draw();
	void update(float fElapsedTime);
	void reset();
};