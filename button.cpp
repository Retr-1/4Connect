#include "button.h"
#include "window.h"

void Button::draw(Window* canvas) {
	canvas->FillRect(olc::vi2d(x, y), olc::vi2d(width, height), olc::WHITE);
	canvas->DrawRect(olc::vi2d(x, y), olc::vi2d(width, height), olc::BLACK);
	canvas->DrawString(olc::vi2d(x + 10, y + 10), this->text, olc::BLACK, 3U);
}

Button::Button(int x, int y, unsigned width, unsigned height, std::string text) {
	this->width = width;
	this->height = height;
	this->x = x;
	this->y = y;
	this->text = text;
}

bool Button::is_pressed(int mx, int my) {
	return mx >= x && my >= y && mx <= x + width && my <= y + height;
}

bool Button::is_pressed(Window* canvas) {
	auto mx = canvas->GetMouseX();
	auto my = canvas->GetMouseY();
	bool pressed = canvas->GetMouse(0).bPressed && mx >= x && my >= y && mx <= x + width && my <= y + height;

	return pressed;
}