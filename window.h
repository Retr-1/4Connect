#pragma once
#include "game.h"
#include "menu.h"

class Window : public olc::PixelGameEngine
{
private:
	enum Projecting {
		GAME,
		MENU
	};

	Game gg;
	Menu mm;
	
	Projecting selected = Projecting::MENU;

public:
	Window();
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
};