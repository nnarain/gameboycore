/**
    \file gameboy.h
    \author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef GAMEBOYCORE_H
#define GAMEBOYCORE_H

#include "gameboycore/gameboycore_api.h"

#include "gameboycore/cpu.h"
#include "gameboycore/mmu.h"
#include "gameboycore/gpu.h"
#include "gameboycore/apu.h"
#include "gameboycore/joypad.h"

#include <stdint.h>

namespace gb
{
    /**
        \brief Encapsulation for Gameboy emulation
    */
    class GAMEBOYCORE_API GameboyCore
    {
    public:
		GameboyCore();
		~GameboyCore();

        void update(int steps = 1);

        void loadROM(uint8_t* rom, uint32_t size);

		void reset();

		void setDebugMode(bool debug);

		CPU& getCPU();
		MMU::Ptr getMMU();
		GPU::Ptr getGPU();
		APU::Ptr getAPU();
		Joy::Ptr getJoypad();

		bool isDone() const;

	private:
		class Impl;
		Impl* impl_;
    };
}

#endif // GAMEBOYCORE_H
