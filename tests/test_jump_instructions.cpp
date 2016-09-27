
/**
	\author Natesh Narain <nnaraindev@gmail.com>
*/

#include <gtest/gtest.h>
#include "test_helper.h"
#include "util/codegenerator.h"

#include <gameboy/gameboy.h>

using namespace gb;

TEST(JumpInstructions, BaseJump)
{
	CodeGenerator code;
	code.block(
		0x76				// halt
	);

	Gameboy gameboy;
	CPU::Status status = run(gameboy, code.rom());

	EXPECT_EQ(status.pc.val, 0x150);
	EXPECT_EQ(status.halt, true);
}

TEST(JumpInstructions, ZFlag)
{
	CodeGenerator code;
	code.block(
		0xC2, 0x50, 0x02	// JP NZ,$250
	);
	code.address(0x250);
	code.block(
		0x06, 0x01,			// LD B,1
		0x05,				// DEC B
		0xCA, 0x00, 0x03	// JP Z,$300
	);
	code.address(0x300);
	code.block(
		0x76				// halt
	);

	Gameboy gameboy;
	CPU::Status status = run(gameboy, code.rom());

	EXPECT_EQ(status.af.lo & CPU::Flags::Z, CPU::Flags::Z);
	EXPECT_EQ(status.pc.val, 0x300);
}

// TODO: Test C Flag Condition

TEST(JumpInstructions, RelativeBase)
{
	CodeGenerator code;
	code.block(
		0xC3, 0x00, 0x02	// JP $200
	);
	code.address(0x200);
	code.block(
		0x18, (uint8_t)-4	// JR -2
	);
	code.address(0x1FE);
	code.block(
		0x76				// halt
	);

	Gameboy gameboy;
	CPU::Status status = run(gameboy, code.rom());

	EXPECT_EQ(status.pc.val, 0x1FE);
}

TEST(JumpInstructions, RelativeZFlag)
{
	CodeGenerator code;
	code.block(
		0x20, 0x10			// JR $10 -> $162
	);
	code.address(0x162);
	code.block(
		0x06, 0x01,			// LD B,1
		0x05,				// DEC B
		0x28, 0x10			// JR $10
	);
	code.address(0x177);
	code.block(
		0x76				// halt
	);

	Gameboy gameboy;
	CPU::Status status = run(gameboy, code.rom());

	EXPECT_EQ(status.af.lo & CPU::Flags::Z, CPU::Flags::Z);
	EXPECT_EQ(status.pc.val, 0x177);
}


// TODO Test Relative Jump with C flag