#pragma once
#include "game.h"

class Window : public olc::PixelGameEngine
{
private:
	Game gg;

public:
	Window();
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
};