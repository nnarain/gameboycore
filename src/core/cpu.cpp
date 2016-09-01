
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
		af_.val = 0;
		bc_.val = 0;
		de_.val = 0;
		hl_.val = 0;
		sp_.val = memorymap::HIGH_RAM_END;
		pc_.val = memorymap::PROGRAM_START;
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

		case 0x76:
			halted_ = true;
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

    bool CPU::isHalted() const
    {
        return halted_;
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
