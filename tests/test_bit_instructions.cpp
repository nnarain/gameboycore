
/**
	\author Natesh Narain <nnaraindev@gmail.com>
	\date Oct 8 2016
*/

#include <gtest/gtest.h>
#include "test_helper.h"

using namespace gb;


TEST(BitInstructions, CheckBit)
{
	CodeGenerator code;
	code.block(
		0x3E, 0x80,		// LD A,$80
		0xCB, 0x7F,		// BIT 7,A
		0x76			// halt
	);

	GameboyCore gameboy;
	CPU::Status status = run(gameboy, code.rom());

	EXPECT_EQ(status.af.hi, 0x80);
	EXPECT_EQ(status.af.lo & CPU::Flags::Z, 0);
	EXPECT_EQ(status.af.lo & CPU::Flags::H, CPU::Flags::H);
	EXPECT_EQ(status.af.lo & CPU::Flags::N, 0);

	code.reset();

	code.block(
		0x2E, 0xEF,		// LD L,$EF
		0xCB, 0x65,		// BIT 4,L
		0x76			// halt
	);

	status = run(gameboy, code.rom());

	EXPECT_EQ(status.hl.lo, 0xEF);
	EXPECT_EQ(status.af.lo & CPU::Flags::Z, CPU::Flags::Z);
	EXPECT_EQ(status.af.lo & CPU::Flags::H, CPU::Flags::H);
	EXPECT_EQ(status.af.lo & CPU::Flags::N, 0);
}

