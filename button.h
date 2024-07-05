#pragma once
#include "olcPixelGameEngine.h"
class Window;

class Button {
public:
	unsigned width;
	unsigned height;
	int x;
	int y;
	std::string text;
	static float lately_pressed;
	static float recharge;

	Button(int x, int y, unsigned width, unsigned height, std::string text = "");
	bool is_pressed(int mx, int my);
	bool is_pressed(Window* canvas);
	void draw(Window* canvas);
};


