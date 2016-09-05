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
		union Register
		{
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

		struct Status
		{
			Register af;
			Register bc;
			Register de;
			Register hl;
			Register sp;
			Register pc;
		};

		enum Flags
		{
			Z = 1 << 7,
			N = 1 << 6,
			H = 1 << 5,
			C = 1 << 4
		};

    public:
        CPU();

        void tick();

		void reset();

        bool isHalted() const;
        const MMU& getMMU() const;
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

		/**
			IN/OUT
		*/
		void in(uint16_t offset);
		void out(uint16_t offset);

		/**
			INC/DEC 
		*/
		void inc(uint8_t&);
		void inc(uint16_t&);
		void inca(uint16_t);
		void dec(uint8_t&);
		void dec(uint16_t&);
		void deca(uint16_t);

		/**
			Push/Pop
		*/

		void push(uint16_t);
		uint16_t pop();

		/**
			Jump
		*/
		void jp(uint16_t);
		void jr(int8_t);

		/**
			Call and Return
		*/
		void call(uint16_t);
		void ret();
		void reti();

		/**
			Swap nybbles in byte
		*/
		uint8_t swap(uint8_t);

		/**
			Decimal Adjust Register A
		*/
		void daa();

	private:
		Register af_;
		Register bc_;
		Register de_;
		Register hl_;
		Register sp_;
		Register pc_;

		MMU mmu_;
		bool halted_;
		bool stopped_;

		uint16_t cycle_count_;
    };
}

#endif // GAMEBOY_CPU_H
