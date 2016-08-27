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
	public:
		using Register = uint16_t;

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

		/**
			get high and low byte of Register
		*/
		uint8_t getH(Register reg);
		uint8_t getL(Register reg);

		void setH(Register& reg, uint8_t);
		void setL(Register& reg, uint8_t);

	private:
		Register af_;
		Register bc_;
		Register de_;
		Register hl_;
		Register sp_;
		Register pc_;

		MMU mmu_;
		bool halted_;

		uint16_t cycle_count_;
    };
}

#endif // GAMEBOY_CPU_H
