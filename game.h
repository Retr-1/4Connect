#pragma once
#include <vector>
#include "olcPixelGameEngine.h"

class Window;
template <typename T> class LinearAnimation;

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

	olc::Pixel token_colors[3] = {olc::WHITE, olc::RED, olc::BLUE};

private:
	void draw_choice(const int& col);
	void drop(const int& col);
	int get_selected_col();
	OccupiedBy check_win();
	LinearAnimation<DropInfo>* lin_anim = nullptr;
	OccupiedBy current_player = OccupiedBy::P1;

	float draw_space1y;
	float draw_space1x;
	float draw_dy;
	float draw_dx;
	float draw_radius;

public:
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
};