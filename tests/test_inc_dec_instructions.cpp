
/**
	Test INC/DEC Instructions on CPU

	@author Natesh Narain <nnaraindev@gmail.com>
*/

#include <gtest/gtest.h>
#include "test_helper.h"
#include "util/codegenerator.h"

#include <gameboy/gameboy.h>

using namespace gb;

TEST(IncDecInstructions, Inc16Bit)
{
	CodeGenerator code;
	code.block(
		0x01, 0x34, 0x12,	// LD BC,$1234
		0x11, 0x78, 0x56,	// LD DE,$5678
		0x21, 0xBC, 0x9A,	// LD HL,$9ABC
		0x31, 0xFE, 0xFF,	// LD SP,$FFFE

		0x03,				// INC BC
		0x13,				// INC DE
		0x23,				// INC HL
		0x33,				// INC SP

		0x76				// halt
	);

	Gameboy gameboy;
	CPU::Status status = run(gameboy, code.rom());

	EXPECT_EQ(status.bc.val, 0x1235);
	EXPECT_EQ(status.de.val, 0x5679);
	EXPECT_EQ(status.hl.val, 0x9ABD);
	EXPECT_EQ(status.sp.val, 0xFFFF);
}

TEST(IncDecInstructions, Dec16Bit)
{
	CodeGenerator code;
	code.block(
		0x01, 0x34, 0x12,	// LD BC,$1234
		0x11, 0x78, 0x56,	// LD DE,$5678
		0x21, 0xBC, 0x9A,	// LD HL,$9ABC
		0x31, 0xFE, 0xFF,	// LD SP,$FFFE

		0x0B,				// DEC BC
		0x1B,				// DEC DE
		0x2B,				// DEC HL
		0x3B,				// DEC SP

		0x76				// halt
	);

	Gameboy gameboy;
	CPU::Status status = run(gameboy, code.rom());

	EXPECT_EQ(status.bc.val, 0x1233);
	EXPECT_EQ(status.de.val, 0x5677);
	EXPECT_EQ(status.hl.val, 0x9ABB);
	EXPECT_EQ(status.sp.val, 0xFFFD);
}

TEST(IncDecInstructions, Inc8Bit)
{
	CodeGenerator code;
	code.block(
		0x3E, 0x01, // LD A,1
		0x06, 0x02, // LD B,2
		0x0E, 0x03, // LD C,3
		0x16, 0x04, // LD D,4
		0x1E, 0x05, // LD E,5
		0x26, 0x06, // LD H,6
		0x2E, 0x07, // LD L,7

		0x3C,		// INC A
		0x04,		// INC B
		0x0C,		// INC C
		0x14,		// INC D
		0x1C,		// INC E
		0x24,		// INC H
		0x2C,		// INC L

		0x76        // halt
	);


	Gameboy gameboy;
	CPU::Status status = run(gameboy, code.rom());

	EXPECT_EQ(status.af.hi, 2);
	EXPECT_EQ(status.bc.hi, 3);
	EXPECT_EQ(status.bc.lo, 4);
	EXPECT_EQ(status.de.hi, 5);
	EXPECT_EQ(status.de.lo, 6);
	EXPECT_EQ(status.hl.hi, 7);
	EXPECT_EQ(status.hl.lo, 8);
}

TEST(IncDecInstructions, Dec8Bit)
{
	CodeGenerator code;
	code.block(
		0x3E, 0x01, // LD A,1
		0x06, 0x02, // LD B,2
		0x0E, 0x03, // LD C,3
		0x16, 0x04, // LD D,4
		0x1E, 0x05, // LD E,5
		0x26, 0x06, // LD H,6
		0x2E, 0x07, // LD L,7

		0x3D,		// DEC A
		0x05,		// DEC B
		0x0D,		// DEC C
		0x15,		// DEC D
		0x1D,		// DEC E
		0x25,		// DEC H
		0x2D,		// DEC L

		0x76        // halt
	);


	Gameboy gameboy;
	CPU::Status status = run(gameboy, code.rom());

	EXPECT_EQ(status.af.hi, 0);
	EXPECT_EQ(status.bc.hi, 1);
	EXPECT_EQ(status.bc.lo, 2);
	EXPECT_EQ(status.de.hi, 3);
	EXPECT_EQ(status.de.lo, 4);
	EXPECT_EQ(status.hl.hi, 5);
	EXPECT_EQ(status.hl.lo, 6);
}

TEST(IncDecInstructions, IncMemory)
{
	CodeGenerator code;
	code.block(
		0x21, 0x00, 0xC0,	// LD HL,$250

		0x35,				// DEC (HL)

		0x76				// halt
	);


	Gameboy gameboy;
	(void)run(gameboy, code.rom());
	const MMU& mmu = gameboy.getCPU().getMMU();

	EXPECT_EQ(mmu.read(0xC000), 0xFF);
}

TEST(IncDecInstructions, DecMemory)
{
	CodeGenerator code;
	code.block(
		0x21, 0x00, 0xC0,	// LD HL,$250

		0x34,				// INC (HL)

		0x76				// halt
	);


	Gameboy gameboy;
	(void)run(gameboy, code.rom());
	const MMU& mmu = gameboy.getCPU().getMMU();

	EXPECT_EQ(mmu.read(0xC000), 0x01);
}


TEST(IncDecInstructions, ZeroFlag)
{
	CodeGenerator code;
	code.block(
		0x06, 0x1,			// LD B,1

		0x05,				// DEC B

		0x76				// halt
	);


	Gameboy gameboy;
	CPU::Status status = run(gameboy, code.rom());

	EXPECT_EQ(status.af.lo & CPU::Flags::Z, CPU::Flags::Z);
	EXPECT_EQ(status.af.lo & CPU::Flags::N, CPU::Flags::N);
}

TEST(IncDecInstructions, HalfCarryFlag)
{
	CodeGenerator code;
	code.block(
		0x06, 0x0F,			// LD B,$0F
		0x04,				// INC B
		0x76				// halt
	);


	Gameboy gameboy;
	CPU::Status status = run(gameboy, code.rom());

	EXPECT_EQ(status.af.lo & CPU::Flags::H, CPU::Flags::H);
	EXPECT_EQ(status.af.lo & CPU::Flags::N, 0);
}

TEST(IncDecInstructions, HalfBorrow)
{
	CodeGenerator code;
	code.block(
		0x06, 0x10,			// LD B,$10
		0x05,				// DEC B
		0x76				// halt
	);


	Gameboy gameboy;
	CPU::Status status = run(gameboy, code.rom());

	EXPECT_EQ(status.af.lo & CPU::Flags::C, 0);
	EXPECT_EQ(status.af.lo & CPU::Flags::H, CPU::Flags::H);
	EXPECT_EQ(status.af.lo & CPU::Flags::N, CPU::Flags::N);
	EXPECT_EQ(status.af.lo & CPU::Flags::Z, 0);
}
