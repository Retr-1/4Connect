#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <iostream>
#include <vector>
#include "window.h"

int main()
{
	//Game demo;
	//if (demo.Construct(256, 240, 4, 4))
	//	demo.Start();
	//return 0;
	Window win;
	if (win.Construct(800, 800, 1, 1)) {
		win.Start();
	}

	return 0;

	//Game test(10, 20, &win);
	//std::cout << test.nrows << test.ncols;
	/*test.playfield[0][0] = Game::OccupiedBy::EMPTY;
	std::cout << test.playfield[1][0];*/
}
