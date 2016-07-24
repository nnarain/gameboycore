
#include "gameboy/cpu.h"

#define WORD(hi, lo) ( (((hi) & 0xFFFF) << 8) | ((lo) & 0xFFFF) )

uint8_t cycles1[] = { 0 };
uint8_t cycles2[] = { 0 };

namespace gb
{
    CPU::CPU() :
        mmu_(),
        halted_(false),
		cycle_count_(0)
    {
		a = 0;
		b = 0;
		c = 0;
		d = 0;
		e = 0;
		f = 0;
		h = 0;
		l = 0;
		sp = memorymap::HIGH_RAM_END;
		pc = memorymap::PROGRAM_START;
    }

    void CPU::tick()
    {
		// fetch next opcode
		uint8_t opcode = mmu_.read(pc++);
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
			opcode = mmu_.read(pc++);
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
	}

	void CPU::decode2(uint8_t opcode)
	{
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
