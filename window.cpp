#include "olcPixelGameEngine.h"
#include "game.h"
#include "window.h"

Window::Window() : gg(6, 6, this), mm(this)
{
		// Name your application
		sAppName = "4Connect";
}

bool Window::OnUserCreate()
{
		// Called once at the start, so create things here
		return true;
}

bool Window::OnUserUpdate(float fElapsedTime)
{
	Button::lately_pressed -= fElapsedTime;
	if (Button::lately_pressed < 0)
		Button::lately_pressed = 0;

	Clear(olc::BLACK);

	if (selected == MENU) {
		mm.update(fElapsedTime);
		mm.draw();
		if (mm.play_vs_bot) {
			gg.pve = true;
			mm.play_vs_bot = false;
			selected = GAME;
		}
		else if (mm.play_vs_human) {
			gg.pve = false;
			mm.play_vs_human = false;
			selected = GAME;
		}
	}
	else if (selected == GAME) {
		gg.update(fElapsedTime);
		gg.draw();

		if (gg.killme) {
			selected = MENU;
			gg.reset();
		}
	}

	std::cout << Button::lately_pressed << '\n';
	

	return true;
}