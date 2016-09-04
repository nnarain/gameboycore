
#include <gtest/gtest.h>
#include "util/codegenerator.h"

#include <gameboy/gameboy.h>

using namespace gb;

TEST(MMUTest, Load)
{
	CodeGenerator code;

	auto rom = code.rom();

	MMU mmu;
	mmu.load(&rom[0], rom.size());
	
	EXPECT_EQ(mmu.numBanks(), 0);
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
	mmu.write(b, 0x512);

	EXPECT_EQ(mmu.read(0x512), 0x35);
}

TEST(MMUTest, Write16Bit)
{
	CodeGenerator code;

	auto rom = code.rom();

	MMU mmu;
	mmu.load(&rom[0], rom.size());

	uint16_t b = 0xDEAD;
	mmu.write(b, 0x512);

	EXPECT_EQ(mmu.read(0x512), 0xAD);
	EXPECT_EQ(mmu.read(0x513), 0xDE);
}
