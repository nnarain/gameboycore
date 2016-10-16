
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

// TODO: MMU Bank loading and ROM bank switching tests

TEST(MMUTest, Read)
{
	CodeGenerator code;
	code.address(0x250);
	code.block(0x1, 0x2);

	auto rom = code.rom();

	MMU mmu;
	mmu.load(&rom[0], rom.size());

	EXPECT_EQ(mmu.read(0x250), 0x1);
	EXPECT_EQ(mmu.read(0x251), 0x2);
}

TEST(MMUTest, Write8Bit)
{
	CodeGenerator code;

	auto rom = code.rom();

	MMU mmu;
	mmu.load(&rom[0], rom.size());

	uint8_t b = 0x35;
	mmu.write(b, 0xC000);

	EXPECT_EQ(mmu.read(0xC000), 0x35);
}

TEST(MMUTest, Write16Bit)
{
	CodeGenerator code;

	auto rom = code.rom();

	MMU mmu;
	mmu.load(&rom[0], rom.size());

	uint16_t b = 0xDEAD;
	mmu.write(b, 0xC000);

	EXPECT_EQ(mmu.read(0xC000), 0xAD);
	EXPECT_EQ(mmu.read(0xC001), 0xDE);
}

TEST(MMUTest, DMA)
{
	CodeGenerator code;
	code.block(
		0x21, 0x00, 0xC0,		// LD HL,$C000
		0x3E, 0x01,				// LD A,1
		0x22,					// LD (HL+),A
		0x3C,					// INC A
		0x22,					// LD (HL+),A
		0x3C,					// INC A
		0x22,					// LD (HL+),A
		0x3C,					// INC A
		0x22,					// LD (HL+),A
		0x3C,					// INC A
		0x22,					// LD (HL+),A
		0x3C,					// INC A

		0x3E, 0xC0,				// LD A,$C0
		0xE0, 0x46,				// LDH (46),A -> LD (FF46),A -> LD (DMA),A

		0x76
	);

	Gameboy gameboy;
	(void)run(gameboy, code.rom());

	const MMU& mmu = gameboy.getCPU().getMMU();

	EXPECT_EQ(mmu.read(memorymap::OAM_START + 0), 1);
	EXPECT_EQ(mmu.read(memorymap::OAM_START + 1), 2);
	EXPECT_EQ(mmu.read(memorymap::OAM_START + 2), 3);
	EXPECT_EQ(mmu.read(memorymap::OAM_START + 3), 4);
	EXPECT_EQ(mmu.read(memorymap::OAM_START + 4), 5);
}