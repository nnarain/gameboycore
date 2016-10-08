/**
    \file gameboy.h
    \author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef GAMEBOY_H
#define GAMEBOY_H

#include "gameboy/cpu.h"
#include "gameboy/tileram.h"
#include "gameboy/tilemap.h"
#include "gameboy/oam.h"
#include "gameboy/joypad.h"

#include <stdint.h>

namespace gb
{
    /**
        \brief Encapsulation for Gameboy emulation
    */
    class Gameboy
    {
    private:
        CPU cpu_;

    public:
        Gameboy();

        void update();

        void loadROM(uint8_t* rom, uint32_t size);

		void reset();

		void setDebugMode(bool debug);

		/**
			Set number of cpu steps to perform before update terminates.
		*/
		void setStepCount(unsigned int step_count);

		const CPU& getCPU() const;

		TileRAM getTileRAM();
		TileMap getTileMap();
		OAM getOAM();

		LCDController& getLCDController();

		Joypad getJoypad();

		bool isDone() const;
    private:
		unsigned int step_count_;
    };
}

#endif // GAMEBOY_H
