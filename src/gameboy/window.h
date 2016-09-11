
/**
	@author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef EMULATOR_WINDOW_H
#define EMULATOR_WINDOW_H

#include <gameboy/tileram.h>

class Window
{
public:
	Window(gb::TileRAM& tile_ram) :
		tile_ram_(tile_ram)
	{
	}

	~Window()
	{
	}

private:
	gb::TileRAM tile_ram_;

};


#endif // !EMULATOR_WINDOW_H

