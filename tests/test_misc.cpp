
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

TEST(MiscInstructions, Swap)
{
	CodeGenerator code;
	code.block(
		0x3E, 0x12, // LD A,$12
		0x06, 0x34, // LD B,$34
		0x0E, 0x56, // LD C,$56
		0x16, 0x78, // LD D,$78
		0x1E, 0x9A, // LD E,$9A
		0x26, 0xBC, // LD H,$BC
		0x2E, 0xDE, // LD L,$DE
		0x36, 0xF0, // LD (HL),$F0

		0xCB, 0x37,	// SWAP A
		0xCB, 0x30,	// SWAP B
		0xCB, 0x31,	// SWAP C
		0xCB, 0x32,	// SWAP D
		0xCB, 0x33,	// SWAP E
		0xCB, 0x36,	// SWAP (HL)
		0xCB, 0x34,	// SWAP H
		0xCB, 0x35,	// SWAP L

		0x76        // halt
	);

	Gameboy gameboy;
	const MMU& mmu = gameboy.getCPU().getMMU();
	CPU::Status status = run(gameboy, code.rom());

	EXPECT_EQ(status.af.hi, 0x21);
	EXPECT_EQ(status.bc.hi, 0x43);
	EXPECT_EQ(status.bc.lo, 0x65);
	EXPECT_EQ(status.de.hi, 0x87);
	EXPECT_EQ(status.de.lo, 0xA9);
	EXPECT_EQ(status.hl.hi, 0xCB);
	EXPECT_EQ(status.hl.lo, 0xED);
	EXPECT_EQ(mmu.read(0xBCDE), 0x0F);
}

TEST(MiscInstructions, ComplementA)
{
	CodeGenerator code;
	code.block(
		0x3E, 0x00, // LD A,$00
		0x2F,		// CPL

		0x76        // halt
	);

	Gameboy gameboy;
	CPU::Status status = run(gameboy, code.rom());

	EXPECT_EQ(status.af.hi, 0xFF);
}
