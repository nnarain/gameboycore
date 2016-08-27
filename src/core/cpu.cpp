
#include "gameboy/cpu.h"

#define WORD(hi, lo) ( (((hi) & 0xFFFF) << 8) | ((lo) & 0xFFFF) )

uint8_t cycles1[] = { 0 };
uint8_t cycles2[] = { 0 };

namespace gb
{
    CPU::CPU() :
        mmu_(),
        halted_(false),
		cycle_count_(0),
		af_(0),
		bc_(0),
		de_(0),
		hl_(0),
		sp_(memorymap::HIGH_RAM_END),
		pc_(memorymap::PROGRAM_START)
    {
    }

    void CPU::tick()
    {
		// fetch next opcode
		uint8_t opcode = mmu_.read(pc_++);
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
			opcode = mmu_.read(pc_++);
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
		}
	}

	void CPU::decode2(uint8_t opcode)
	{
		switch (opcode)
		{
		}
	}

	uint8_t CPU::load8Imm()
	{
		return mmu_.read(pc_++);
	}

	uint16_t CPU::load16Imm()
	{
		uint8_t lo = load8Imm();
		uint8_t hi = load8Imm();

		return WORD(hi, lo);
	}

	uint8_t CPU::getH(Register reg)
	{
		return (reg & 0xFF00) >> 8;
	}

	uint8_t CPU::getL(Register reg)
	{
		return (uint8_t)(reg & 0x00FF);
	}

	void CPU::setH(Register& reg, uint8_t hi)
	{
		reg = ((hi & 0xFFFF) << 8) | (reg & 0x00FF);
	}
	
	void CPU::setL(Register& reg, uint8_t lo)
	{
		reg = (reg & 0xFF00) | (lo & 0x00FF);
	}

    bool CPU::isHalted() const
    {
        return halted_;
    }

    MMU& CPU::getMMU()
    {
        return mmu_;
    }
}
