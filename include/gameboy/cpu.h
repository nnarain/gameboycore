/**
    \file cpu.h
    \author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef GAMEBOY_CPU_H
#define GAMEBOY_CPU_H

#include "gameboy/mmu.h"
#include <stdint.h>

namespace gb
{
    class CPU
    {
    private:
		uint8_t a, f;
		uint8_t b, c;
		uint8_t d, e;
		uint8_t h, l;
		uint16_t sp;
		uint16_t pc;

        MMU mmu_;
        bool halted_;

		uint16_t cycle_count_;

    public:
        CPU();

        void tick();

		void decode1(uint8_t opcode);
		void decode2(uint8_t opcode);

        bool isHalted() const;
        MMU& getMMU();
    };
}

#endif // GAMEBOY_CPU_H
