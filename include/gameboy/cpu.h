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
		struct Register
		{
			union {
				struct {
#ifdef __LITTLEENDIAN__
					uint8_t lo;
					uint8_t hi;
#else
					uint8_t hi;
					uint8_t lo;
#endif
				};
				uint16_t val;
			};

			Register() {}
			Register(uint16_t val) : val(val) {}
		};

		struct Status
		{
			Register af;
			Register bc;
			Register de;
			Register hl;
			Register sp;
			Register pc;
		};

    public:
        CPU();

        void tick();

        bool isHalted() const;
        MMU& getMMU();

		Status getStatus() const;

	private:
		void decode1(uint8_t opcode);
		void decode2(uint8_t opcode);

		/**
			Load 8 bit integer immediately from memory
		*/
		uint8_t load8Imm();
		uint16_t load16Imm();

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
