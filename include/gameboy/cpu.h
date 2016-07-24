/**
    \file cpu.h
    \author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef GAMEBOY_CPU_H
#define GAMEBOY_CPU_H

// check endianness
#if !defined(__BIGENDIAN__) && !defined(__LITTLEENDIAN__)
#	error "Either __BIGENDIAN__ or __LITTLEENDIAN__ must be defined"
#endif

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

        bool isHalted() const;
        MMU& getMMU();

	private:
		void decode1(uint8_t opcode);
		void decode2(uint8_t opcode);

		/**
			Load 8 bit integer immediately from memory
		*/
		uint8_t load8Imm();
		uint16_t load16Imm();
    };
}

#endif // GAMEBOY_CPU_H
