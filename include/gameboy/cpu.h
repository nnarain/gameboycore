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
#include "gameboy/alu.h"
#include "gameboy/opcodeinfo.h"

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

		enum class InterruptMask
		{
			VBLANK                   = 1 << 0,
			LCDC_STAT                = 1 << 1,
			TIME_OVERFLOW            = 1 << 2,
			SERIAL_TRANSFER_COMPLETE = 1 << 3,
			JOYPAD                   = 1 << 4
		};

		enum class InterruptVector
		{
			VBLANK                   = 0x0040,
			LCDC_STAT                = 0x0048,
			TIME_OVERFLOW            = 0x0050,
			SERIAL_TRANSFER_COMPLETE = 0x0058,
			JOYPAD                   = 0x0060
		};

    public:
        CPU();

        void tick();

		void reset();

        bool isHalted() const;
        const MMU& getMMU() const;
		MMU& getMMU();

		void setDebugMode(bool debug_mode);

		Status getStatus() const;

	private:
		void decode1(uint8_t opcode);
		void decode2(uint8_t opcode);

		void checkInterrupts();
		void interrupt(InterruptVector);

		void printDisassembly(uint8_t opcode, uint16_t userdata_ptr, OpcodePage page);

		/* Instruction Implementation Helper Functions */

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

		/**
			Bit
		*/
		void bit(uint8_t val, uint8_t bit);

	private:
		Register af_;
		Register bc_;
		Register de_;
		Register hl_;
		Register sp_;
		Register pc_;

		MMU mmu_;
		ALU alu_;

		bool halted_;
		bool stopped_;

		bool interrupt_master_enable_;
		int interrupt_master_enable_pending_;
		int interrupt_master_disable_pending_;

		bool debug_mode_;

		uint16_t cycle_count_;
    };
}

#endif // GAMEBOY_CPU_H
