#pragma once
#include "window.h"
#include "olcPixelGameEngine.h"

class Button {
public:
	unsigned width;
	unsigned height;
	int x;
	int y;
	std::string text;

	Button(int x, int y, unsigned width, unsigned height, std::string text="") {
		this->width = width;
		this->height = height;
		this->x = x;
		this->y = y;
		this->text = text;
	}

	bool is_pressed(int mx, int my) {
		return mx >= x && my >= y && mx <= x + width && my <= y + height;
	}

	void draw(Window& canvas) {
		canvas.FillRect(olc::vi2d(x, y), olc::vi2d(width, height), olc::WHITE);
		canvas.DrawRect(olc::vi2d(x, y), olc::vi2d(width, height), olc::BLACK);
		canvas.DrawString(olc::vi2d(x+10, y+10), this->text, olc::BLACK, 3U);
	}
};
