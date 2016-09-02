/**
	Test Load Instructions on CPU
	
	@author Natesh Narain <nnaraindev@gmail.com>
*/

#include <gtest/gtest.h>
#include "util/codegenerator.h"

#include <gameboy/gameboy.h>

using namespace gb;

TEST(LoadInstructionsTest, Load8BitImmediate)
{
	// test load immediate for all registers

	CodeGenerator code;
	code.block(
		0x3E, 0x01, // LD A,1
		0x06, 0x02, // LD B,2
		0x0E, 0x03, // LD C,3
		0x16, 0x04, // LD D,4
		0x1E, 0x05, // LD E,5
		0x26, 0x06, // LD H,6
		0x2E, 0x07, // LD L,7

		0x76        // halt
	);

	
	Gameboy gameboy;

	auto rom = code.rom();
	gameboy.loadROM(&rom[0], rom.size());

	while (!gameboy.isDone())
		gameboy.update();

	CPU::Status status = gameboy.getCPU().getStatus();
	
	EXPECT_EQ(status.af.hi, 1);
	EXPECT_EQ(status.bc.hi, 2);
	EXPECT_EQ(status.bc.lo, 3);
	EXPECT_EQ(status.de.hi, 4);
	EXPECT_EQ(status.de.lo, 5);
	EXPECT_EQ(status.hl.hi, 6);
	EXPECT_EQ(status.hl.lo, 7);
}

TEST(LoadInstructionsTest, Load16BitImmediate)
{
	// test load immediate for all registers

	CodeGenerator code;
	code.block(
		0x01, 0x34, 0x12, // LD BC,$1234
		0x11, 0x78, 0x56, // LD DE,$5678
		0x21, 0xBC, 0x9A, // LD HL,$9ABC
		0x31, 0xFE, 0xFF, // LD SP,$FFFE

		0x76              // halt
	);

	
	Gameboy gameboy;

	auto rom = code.rom();
	gameboy.loadROM(&rom[0], rom.size());

	while (!gameboy.isDone())
		gameboy.update();

	CPU::Status status = gameboy.getCPU().getStatus();
	
	EXPECT_EQ(status.bc.val, 0x1234);
	EXPECT_EQ(status.de.val, 0x5678);
	EXPECT_EQ(status.hl.val, 0x9ABC);
	EXPECT_EQ(status.sp.val, 0xFFFE);
}

int main(int argc, char * argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

