/**
    \file gameboy.h
    \author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef GAMEBOY_H
#define GAMEBOY_H

#include "gameboy/cpu.h"
#include "gameboy/mmu.h"
#include "gameboy/gpu.h"
#include "gameboy/apu.h"
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

#endif // GAMEBOY_H
