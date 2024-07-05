#include "menu.h"
#include "button.h"
#include "window.h"


Menu::Menu(Window* canvas) : play_vs_human_btn(0, 0, 0, 0, "Play Against Human"), play_vs_bot_btn(0, 0, 0, 0, "Play Against Computer") {
	this->canvas = canvas;
}

void Menu::update_sizes() {
	int w = canvas->ScreenWidth() * 0.8;
	int h = 200;
	int gap = 10;
	int total_h = 2 * h + gap;
	int x = (canvas->ScreenWidth() - w) / 2;
	int y = canvas->ScreenHeight() / 2 - total_h/2;
	

	play_vs_human_btn.width = w;
	play_vs_human_btn.height = h;
	play_vs_human_btn.x = x;
	play_vs_human_btn.y = y;

	play_vs_bot_btn.height = h;
	play_vs_bot_btn.width = w;
	play_vs_bot_btn.x = x;
	play_vs_bot_btn.y = y + h + gap;
}

void Menu::update(const float& fElapsedTime) {
	update_sizes();

	if (play_vs_human_btn.is_pressed(canvas)) {
		play_vs_human = true;
	}
	else if (play_vs_bot_btn.is_pressed(canvas)) {
		play_vs_bot = true;
	}

}

void Menu::draw() {
	play_vs_human_btn.draw(canvas);
	play_vs_bot_btn.draw(canvas);
}
