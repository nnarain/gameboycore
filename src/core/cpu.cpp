
#include "gameboy/cpu.h"

#include <iostream>

#define WORD(hi, lo) ( (((hi) & 0xFFFF) << 8) | ((lo) & 0xFFFF) )

#include "bitutil.h"

uint8_t cycles1[] = { 0 };
uint8_t cycles2[] = { 0 };

namespace gb
{
	CPU::CPU() :
		mmu_(),
		halted_(false),
		cycle_count_(0)
	{
		reset();
	}

	void CPU::tick()
	{
		// fetch next opcode
		uint8_t opcode = mmu_.read(pc_.val++);
		uint8_t cycles;

		// $CB means decode from the second page of instructions
		if (opcode != 0xCB)
		{
			// decode from first page
			decode1(opcode);

			// look up the number of cycles for this opcode
			cycles = cycles1[opcode];
		}
		else
		{
			// read the second page opcode
			opcode = mmu_.read(pc_.val++);
			// decode from second page
			decode2(opcode);

			// look up the number of cycles for this opcode
			cycles = cycles2[opcode];
		}

		cycle_count_ += cycles;

		// TODO: determine what interrupts should fire
	}

	void CPU::decode1(uint8_t opcode)
	{
		switch (opcode)
		{
		case 0x00:
			// NOP
			break;
		case 0x10:
			stopped_ = true;
			break;

			// Load Instructions

			// 8 bit loads immediate
		case 0x3E: // LD A,d8
			af_.hi = load8Imm();
			break;
		case 0x06: // LD B,d8
			bc_.hi = load8Imm();
			break;
		case 0x0E: // LD C,d8
			bc_.lo = load8Imm();
			break;
		case 0x16: // LD D,d8
			de_.hi = load8Imm();
			break;
		case 0x1E: // LD E,d8
			de_.lo = load8Imm();
			break;
		case 0x26: // LD H,d8
			hl_.hi = load8Imm();
			break;
		case 0x2E: // LD L,d8
			hl_.lo = load8Imm();
			break;

			// load 16 bit immediate
		case 0x01: // LD BC,d16
			bc_.val = load16Imm();
			break;
		case 0x11: // LD DE,d16
			de_.val = load16Imm();
			break;
		case 0x21: // LD HL,d16
			hl_.val = load16Imm();
			break;
		case 0x31: // LD SP,d16
			sp_.val = load16Imm();
			break;

			// transfer (Register to register, memory to register)
		case 0x40: // LD B,B
			bc_.hi = bc_.hi;
			break;
		case 0x41: // LD B,C
			bc_.hi = bc_.lo;
			break;
		case 0x42: // LD B,D
			bc_.hi = de_.hi;
			break;
		case 0x43: // LD B,E
			bc_.hi = de_.lo;
			break;
		case 0x44: // LD B,H
			bc_.hi = hl_.hi;
			break;
		case 0x45: // LD B,L
			bc_.hi = hl_.lo;
			break;
		case 0x46: // LD B,(HL)
			bc_.hi = mmu_.read(hl_.val);
			break;
		case 0x47: // LD B,A
			bc_.hi = af_.hi;
			break;
		case 0x48: // LD C,B
			bc_.lo = bc_.hi;
			break;
		case 0x49: // LD C,C
			bc_.lo = bc_.lo;
			break;
		case 0x4A: // LD C,D
			bc_.lo = de_.hi;
			break;
		case 0x4B: // LD C,E
			bc_.lo = de_.lo;
			break;
		case 0x4C: // LD C,H
			bc_.lo = hl_.hi;
			break;
		case 0x4D: // LD C,L
			bc_.lo = hl_.lo;
			break;
		case 0x4E: // LD C,(HL)
			bc_.lo = mmu_.read(hl_.val);
			break;
		case 0x4F: // LD C,A
			bc_.lo = af_.hi;
			break;

		case 0x50: // LD D,B
			de_.hi = bc_.hi;
			break;
		case 0x51: // LD D,C
			de_.hi = bc_.lo;
			break;
		case 0x52: // LD D,D
			de_.hi = de_.hi;
			break;
		case 0x53: // LD D,E
			de_.hi = de_.lo;
			break;
		case 0x54: // LD D,H
			de_.hi = hl_.hi;
			break;
		case 0x55: // LD D,L
			de_.hi = hl_.lo;
			break;
		case 0x56: // LD D,(HL)
			de_.hi = mmu_.read(hl_.val);
			break;
		case 0x57: // LD D,A
			de_.hi = af_.hi;
			break;
		case 0x58: // LD E,B
			de_.lo = bc_.hi;
			break;
		case 0x59: // LD E,C
			de_.lo = bc_.lo;
			break;
		case 0x5A: // LD E,D
			de_.lo = de_.hi;
			break;
		case 0x5B: // LD E,E
			de_.lo = de_.lo;
			break;
		case 0x5C: // LD E,H
			de_.lo = hl_.hi;
			break;
		case 0x5D: // LD E,L
			de_.lo = hl_.lo;
			break;
		case 0x5E: // LD E,(HL)
			de_.lo = mmu_.read(hl_.val);
			break;
		case 0x5F: // LD E,A
			de_.lo = af_.hi;
			break;

		case 0x60: // LD H,B
			hl_.hi = bc_.hi;
			break;
		case 0x61: // LD H,C
			hl_.hi = bc_.lo;
			break;
		case 0x62: // LD H,D
			hl_.hi = de_.hi;
			break;
		case 0x63: // LD H,E
			hl_.hi = de_.lo;
			break;
		case 0x64: // LD H,H
			hl_.hi = hl_.hi;
			break;
		case 0x65: // LD H,L
			hl_.hi = hl_.lo;
			break;
		case 0x66: // LD H,(HL)
			hl_.hi = mmu_.read(hl_.val);
			break;
		case 0x67: // LD H,A
			hl_.hi = af_.hi;
			break;
		case 0x68: // LD L,B
			hl_.lo = bc_.hi;
			break;
		case 0x69: // LD L,C
			hl_.lo = bc_.lo;
			break;
		case 0x6A: // LD L,D
			hl_.lo = de_.hi;
			break;
		case 0x6B: // LD L,E
			hl_.lo = de_.lo;
			break;
		case 0x6C: // LD L,H
			hl_.lo = hl_.hi;
			break;
		case 0x6D: // LD L,L
			hl_.lo = hl_.lo;
			break;
		case 0x6E: // LD L,(HL)
			hl_.lo = mmu_.read(hl_.val);
			break;
		case 0x6F: // LD L,A
			hl_.lo = af_.hi;
			break;

		case 0x78: // LD A,B
			af_.hi = bc_.hi;
			break;
		case 0x79: // LD A,C
			af_.hi = bc_.lo;
			break;
		case 0x7A: // LD A,D
			af_.hi = de_.hi;
			break;
		case 0x7B: // LD A,E
			af_.hi = de_.lo;
			break;
		case 0x7C: // LD A,H
			af_.hi = hl_.hi;
			break;
		case 0x7D: // LD A,L
			af_.hi = hl_.lo;
			break;
		case 0x7E: // LD A,(HL)
			af_.hi = mmu_.read(hl_.val);
			break;
		case 0x7F: // LD A,A
			af_.hi = af_.hi;
			break;

			// register to memory
		case 0x70: // LD (HL),B
			mmu_.write(bc_.hi, hl_.val);
			break;
		case 0x71: // LD (HL),C
			mmu_.write(bc_.lo, hl_.val);
			break;
		case 0x72: // LD (HL),D
			mmu_.write(de_.hi, hl_.val);
			break;
		case 0x73: // LD (HL),E
			mmu_.write(de_.lo, hl_.val);
			break;
		case 0x74: // LD (HL),H
			mmu_.write(hl_.hi, hl_.val);
			break;
		case 0x75: // LD (HL),L
			mmu_.write(hl_.lo, hl_.val);
			break;
		case 0x77: // LD (HL),A
			mmu_.write(af_.hi, hl_.val);
			break;

		// Load Increment/Decrement
		// (HL+/-) <- A & A <- (HL+/-)
		case 0x22: // LD (HL+),A
			mmu_.write(af_.hi, hl_.val++);
			break;
		case 0x32: // LD (HL-),A
			mmu_.write(af_.hi, hl_.val--);
			break;
		case 0x2A: // LD A,(HL+)
			af_.hi = mmu_.read(hl_.val++);
			break;
		case 0x3A: // LD A,(HL-)
			af_.hi = mmu_.read(hl_.val--);
			break;

		// IN/OUT Instructions. Load and Store to IO Registers (immediate or using C register). IO Offset is $FF00
		case 0xE0: // LDH (a8),A
			out(load8Imm());
			break;
		case 0xF0: // LDH A,(a8)
			in(load8Imm());
			break;
		case 0xE2: // LD (C),A
			out(bc_.lo);
			break;
		case 0xF2: // LD A,(C)
			in(bc_.lo);
			break;
		case 0xEA: // LD (a16),A
			out(load16Imm());
			break;
		case 0xFA: // LD A,(a16)
			in(load16Imm());
			break;

		/* Increment Instruction */

		// 16 bit increment
		case 0x03: // INC BC
			inc(bc_.val);
			break;
		case 0x13: // INC DE
			inc(de_.val);
			break;
		case 0x23: // INC HL
			inc(hl_.val);
			break;
		case 0x33: // INC SP
			inc(sp_.val);
			break;

		// 16 bit decrement
		case 0x0B: // DEC BC
			dec(bc_.val);
			break;
		case 0x1B: // DEC DE
			dec(de_.val);
			break;
		case 0x2B: // DEC HL
			dec(hl_.val);
			break;
		case 0x3B: // DEC SP
			dec(sp_.val);
			break;

		// 8 bit increment
		case 0x04: // INC B
			inc(bc_.hi);
			break;
		case 0x0C: // INC C
			inc(bc_.lo);
			break;
		case 0x14: // INC D
			inc(de_.hi);
			break;
		case 0x1C: // INC E
			inc(de_.lo);
			break;
		case 0x24: // INC H
			inc(hl_.hi);
			break;
		case 0x2C: // INC L
			inc(hl_.lo);
			break;
		case 0x34: // INC (HL)
			inca(hl_.val);
			break;
		case 0x3C: // INC A
			inc(af_.hi);
			break;

		// 8 bit decrement
		case 0x05: // DEC B
			dec(bc_.hi);
			break;
		case 0x0D: // DEC C
			dec(bc_.lo);
			break;
		case 0x15: // DEC D
			dec(de_.hi);
			break;
		case 0x1D: // DEC C
			dec(de_.lo);
			break;
		case 0x25: // DEC H
			dec(hl_.hi);
			break;
		case 0x2D: // DEC L
			dec(hl_.lo);
			break;
		case 0x35: // DEC (HL)
			deca(hl_.val);
			break;
		case 0x3D: // DEC A
			dec(af_.hi);
			break;

		/* Stack Instructions */

		// Push
		case 0xC5: // PUSH BC
			push(bc_.val);
			break;
		case 0xD5: // PUSH DE
			push(de_.val);
			break;
		case 0xE5: // PUSH HL
			push(hl_.val);
			break;
		case 0xF5: // PUSH AF
			push(af_.val);
			break;

		// Pop
		case 0xC1: // POP BC
			bc_.val = pop();
			break;
		case 0xD1: // POP DE
			de_.val = pop();
			break;
		case 0xE1: // POP HL
			hl_.val = pop();
			break;
		case 0xF1: // POP AF
			af_.val = pop();
			break;

		// Load

		case 0x08: // LD (a16),SP
			mmu_.write(sp_.val, load16Imm());
			break;
		case 0xF8: // LD HL,SP+r8
			hl_.val = (uint16_t)((int16_t)sp_.val + (int8_t)load8Imm());
			break;
		case 0xF9: // LD SP,HL
			sp_.val = hl_.val;
			break;

		case 0x76:
			halted_ = true;
			break;

		/* Jumps */
		case 0xC3: // JP a16
			jp(load16Imm());
			break;

		case 0xE9:	// JP (HL)
			jp(hl_.val);
			break;

		// conditional jumps
		case 0xC2: // JP NZ,nn
			if (IS_CLR(af_.lo, Flags::Z)) jp(load16Imm());
			break;
		case 0xCA: // JP Z,nn
			if (IS_SET(af_.lo, Flags::Z)) jp(load16Imm());
			break;
		case 0xD2: // JP NC,nn
			if (IS_CLR(af_.lo, Flags::C)) jp(load16Imm());
			break;
		case 0xDA: // JP C,nn
			if (IS_SET(af_.lo, Flags::C)) jp(load16Imm());
			break;

		// relative jumps
		case 0x18: // JR r8
			jr((int8_t)load8Imm());
			break;

		// relative conditional jumps
		case 0x20: // JR NZ,n
			if (IS_CLR(af_.lo, Flags::Z)) jr((int8_t)load8Imm());
			break;
		case 0x28: // JR Z,n
			if (IS_SET(af_.lo, Flags::Z)) jr((int8_t)load8Imm());
			break;
		case 0x30: // JR NC,n
			if(IS_CLR(af_.lo, Flags::C)) jr((int8_t)load8Imm());
			break;
		case 0x38: // JR C,n
			if (IS_SET(af_.lo, Flags::C)) jr((int8_t)load8Imm());
			break;

		/* Call */
		case 0xCD: // CALL nn
			call(load16Imm());
			break;

		// call condition
		case 0xC4: // CALL NZ,nn
			if (IS_CLR(af_.lo, Flags::Z)) call(load16Imm());
			break;
		case 0xCC: // CALL Z,nn
			if (IS_SET(af_.lo, Flags::Z)) call(load16Imm());
			break;
		case 0xD4: // CALL NC,nn
			if (IS_CLR(af_.lo, Flags::C)) call(load16Imm());
			break;
		case 0xDC: // CALL C,nn
			if (IS_SET(af_.lo, Flags::C)) call(load16Imm());
			break;

		/* Returns */
		case 0xC9: // RET
			ret();
			break;

		// conditional returns
		case 0xC0: // RET NZ
			if (IS_CLR(af_.lo, Flags::Z)) ret();
			break;
		case 0xC8: // RET Z
			if (IS_SET(af_.lo, Flags::Z)) ret();
			break;
		case 0xD0: // RET NC
			if (IS_CLR(af_.lo, Flags::C)) ret();
			break;
		case 0xD8: // RET C
			if (IS_SET(af_.lo, Flags::C)) ret();
			break;

		// return from interrupt
		case 0xD9: // RETI
			reti();
			break;

		/* Reset Instructions */
		case 0xC7: // RST $00
			call(0x00);
			break;
		case 0xCF: // RST $08
			call(0x08);
			break;
		case 0xD7: // RST $10
			call(0x10);
			break;
		case 0xDF: // RST $18
			call(0x18);
			break;
		case 0xE7: // RST $20
			call(0x20);
			break;
		case 0xEF: // RST $28
			call(0x28);
			break;
		case 0xF7: // RST $30
			call(0x30);
			break;
		case 0xFF: // RST $38
			call(0x38);
			break;
		}
	}

	void CPU::decode2(uint8_t opcode)
	{
		switch (opcode)
		{
		case 0x00:
			break;
		default:
			break;
		}
	}

	uint8_t CPU::load8Imm()
	{
		return mmu_.read(pc_.val++);
	}

	uint16_t CPU::load16Imm()
	{
		uint8_t lo = load8Imm();
		uint8_t hi = load8Imm();

		return WORD(hi, lo);
	}

	void CPU::in(uint16_t offset)
	{
		// read from offset into IO registers
		af_.hi = mmu_.read(0xFF00 + offset);
	}

	void CPU::out(uint16_t offset)
	{
		// write out to the IO registers given the offset
		mmu_.write(af_.hi, 0xFF00 + offset);
	}

	void CPU::inc(uint8_t& i)
	{
		bool half_carry = IS_HALF_CARRY(i, 1);

		i++;
		
		if (i == 0) SET(af_.lo, Flags::Z);
		CLR(af_.lo, Flags::N);
		if (half_carry)
			SET(af_.lo, Flags::H);
		else
			CLR(af_.lo, Flags::H);
	}
	
	void CPU::inc(uint16_t& i)
	{
		i++;
	}
	
	void CPU::dec(uint8_t& d)
	{
		bool half_carry = IS_HALF_CARRY(d, -1);

		d--;
		
		if (d == 0) SET(af_.lo, Flags::Z);
		SET(af_.lo, Flags::N);
		if (half_carry)
			SET(af_.lo, Flags::H);
		else
			CLR(af_.lo, Flags::H);
	}

	void CPU::dec(uint16_t& d)
	{
		d--;
	}

	void CPU::inca(uint16_t addr)
	{
		uint8_t b = mmu_.read(addr);
		inc(b);
		mmu_.write(b, addr);
	}

	void CPU::deca(uint16_t addr)
	{
		uint8_t b = mmu_.read(addr);
		dec(b);
		mmu_.write(b, addr);
	}

	void CPU::push(uint16_t value)
	{
		uint8_t hi = (value & 0xFF00) >> 8;
		uint8_t lo = (value & 0x00FF);

		mmu_.write(hi, sp_.val - 1);
		mmu_.write(lo, sp_.val - 2);

		sp_.val -= 2;
	}

	uint16_t CPU::pop()
	{
		uint8_t lo = mmu_.read(sp_.val);
		uint8_t hi = mmu_.read(sp_.val + 1);

		sp_.val += 2;

		return WORD(hi, lo);
	}

	void CPU::jp(uint16_t addr)
	{
		pc_.val = addr;
	}

	void CPU::jr(int8_t r)
	{
		pc_.val += r;
	}

	void CPU::call(uint16_t addr)
	{
		push(pc_.val);
		pc_.val = addr;
	}

	void CPU::ret()
	{
		pc_.val = pop();
	}

	void CPU::reti()
	{
		ret();
		// TODO: Enable Interrutps
	}

	void CPU::reset()
	{
		af_.val = 0;
		bc_.val = 0;
		de_.val = 0;
		hl_.val = 0;
		sp_.val = memorymap::HIGH_RAM_END;
		pc_.val = memorymap::PROGRAM_START;

		cycle_count_ = 0;
		halted_ = false;
		stopped_ = false;
	}

    bool CPU::isHalted() const
    {
        return halted_;
    }

    const MMU& CPU::getMMU() const
    {
        return mmu_;
    }
	MMU& CPU::getMMU()
	{
		return mmu_;
	}

	CPU::Status CPU::getStatus() const
	{
		Status status;
		status.af = af_;
		status.bc = bc_;
		status.de = de_;
		status.hl = hl_;
		status.sp = sp_;
		status.pc = pc_;

		return status;
	}

}
