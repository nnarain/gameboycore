/**
	Test Arithmetic Instructions on CPU

	@author Natesh Narain <nnaraindev@gmail.com>
*/

#include <gtest/gtest.h>
#include "util/codegenerator.h"

#include <gameboy/gameboy.h>

using namespace gb;

static CPU::Status run(Gameboy& gameboy, std::vector<uint8_t>& rom)
{
	gameboy.loadROM(&rom[0], rom.size());

	while (!gameboy.isDone())
		gameboy.update();

	CPU::Status status = gameboy.getCPU().getStatus();

	gameboy.reset();

	return status;
}

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


	Gameboy gameboy;
	CPU::Status status = run(gameboy, code.rom());

	EXPECT_EQ(status.af.hi, 0x00);
	EXPECT_EQ(status.af.lo & CPU::Flags::C, CPU::Flags::C);
	EXPECT_EQ(status.af.lo & CPU::Flags::Z, CPU::Flags::Z);
	EXPECT_EQ(status.af.lo & CPU::Flags::N, 0);
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


	Gameboy gameboy;
	CPU::Status status = run(gameboy, code.rom());

	EXPECT_EQ(status.af.hi, 0x10);
	EXPECT_EQ(status.af.lo & CPU::Flags::H, CPU::Flags::H);
	EXPECT_EQ(status.af.lo & CPU::Flags::N, 0);
}