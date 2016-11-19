/**
    \file gameboycore.h
    \brief Encapsulate Gameboy hardware
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
        \class GameboyCore
        \ingroup API
    */
    class GAMEBOYCORE_API GameboyCore
    {
    public:
		GameboyCore();
		~GameboyCore();

        /**
        	runs `steps` number of steps on the gameboycore
        */
        void update(int steps = 1);

        /**
            Load byte buffer into virtual memory
        */
        void loadROM(uint8_t* rom, uint32_t size);

        /**
            Reset the GameboyCore state
        */
		void reset();

		void setDebugMode(bool debug);

		CPU::Ptr& getCPU();
		MMU::Ptr& getMMU();
		GPU::Ptr& getGPU();
		APU::Ptr& getAPU();
		Joy::Ptr& getJoypad();

		bool isDone() const;

	private:
		class Impl;
		Impl* impl_;
    };
}

#endif // GAMEBOYCORE_H
