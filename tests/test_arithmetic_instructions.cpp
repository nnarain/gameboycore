/**
	Test Arithmetic Instructions on CPU

	@author Natesh Narain <nnaraindev@gmail.com>
*/

#include <gtest/gtest.h>
#include "test_helper.h"

#include <gameboycore/gameboycore.h>

using namespace gb;

TEST(ArithmeticTests, AddOverflow)
{
	// test load immediate for all registers

	CodeGenerator code;
	code.block(
		0x3E, 0xFF, // LD A,FF
		0x06, 0x01, // LD B,01

		0x80,		// ADD A,B

		0x76        // halt
	);


	GameboyCore gameboy;
	CPU::Status status = run(gameboy, code.rom());

	EXPECT_EQ(status.a, 0x00);
	EXPECT_EQ(status.f & CPU::Flags::C, CPU::Flags::C);
	EXPECT_EQ(status.f & CPU::Flags::Z, CPU::Flags::Z);
	EXPECT_EQ(status.f & CPU::Flags::N, 0);
}

TEST(ArithmeticTests, AddHalfCarry)
{
	CodeGenerator code;
	code.block(
		0x3E, 0x0F, // LD A,FF
		0x06, 0x01, // LD B,01

		0x80,		// ADD A,B

		0x76        // halt
	);


	GameboyCore gameboy;
	CPU::Status status = run(gameboy, code.rom());

	EXPECT_EQ(status.a, 0x10);
	EXPECT_EQ(status.f & CPU::Flags::H, CPU::Flags::H);
	EXPECT_EQ(status.f & CPU::Flags::N, 0);
}