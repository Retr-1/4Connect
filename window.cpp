#include "olcPixelGameEngine.h"
#include "game.h"
#include "window.h"

Window::Window() : gg(6,6,this)
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
		Clear(olc::BLACK);
		gg.update(fElapsedTime);
		gg.draw();
		return true;
}