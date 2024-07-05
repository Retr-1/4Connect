#pragma once
#include "button.h"

class Window;

class Menu {
private:
	Button play_vs_human_btn;
	Button play_vs_bot_btn;
	Window* canvas;

	void update_sizes();

public:
	bool play_vs_human = false;
	bool play_vs_bot = false;

	Menu(Window* canvas);
	void update(const float& fElapsedTime);
	void draw();
};