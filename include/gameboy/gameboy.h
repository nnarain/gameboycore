/**
    \file gameboy.h
    \author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef GAMEBOY_H
#define GAMEBOY_H

#include "gameboy/cpu.h"
#include "gameboy/display.h"

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

		const CPU& getCPU() const;

		Display getDisplay();

		bool isDone() const;
    private:
    };
}

#endif // GAMEBOY_H
