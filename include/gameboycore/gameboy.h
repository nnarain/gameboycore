/**
    \file gameboy.h
    \author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef GAMEBOYCORE_H
#define GAMEBOYCORE_H

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
    class Gameboy
    {
    private:
		CPU::Ptr cpu_;
		MMU::Ptr mmu_;
		GPU::Ptr gpu_;
		APU::Ptr apu_;

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

		CPU& getCPU();
		MMU::Ptr getMMU();
		GPU::Ptr getGPU();
		APU::Ptr getAPU();

		Joypad getJoypad();

		bool isDone() const;
    private:
		unsigned int step_count_;
    };
}

#endif // GAMEBOYCORE_H
