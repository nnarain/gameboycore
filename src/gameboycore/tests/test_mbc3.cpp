#include <gtest/gtest.h>
#include <gameboycore/gameboycore.h>

#include "util/codegenerator.h"

using namespace gb;

TEST(MBC3, BankRemap)
{
    /**
        Banks $20, $40 and $60 supported
    */

    CodeGenerator code{ CodeGenerator::MBC::MBC3 };

    code.address(0x4000, 0x20);
    code.block(0xAA);

    code.address(0x4000, 0x40);
    code.block(0xBB);

    code.address(0x4000, 0x60);
    code.block(0xCC);

    GameboyCore core;
    core.loadROM(code.rom());

    // $4000 -> upper 2 bits
    // $2000 -> lower 5 bits

    // Swap to banks $20, $40 and $60

    // Bank swap to Bank $20
    core.writeMemory(0x2000, 0x20);
    const auto value1 = core.readMemory(0x4000);

    // Bank swap to Bank $40
    core.writeMemory(0x2000, 0x40);
    const auto value2 = core.readMemory(0x4000);

    // Bank swap to Bank $60
    core.writeMemory(0x2000, 0x60);
    const auto value3 = core.readMemory(0x4000);

    EXPECT_EQ(value1, 0xAA);
    EXPECT_EQ(value2, 0xBB);
    EXPECT_EQ(value3, 0xCC);
}


TEST(MBC3, RTC)
{
	CodeGenerator code{ CodeGenerator::MBC::MBC3 };
	code.block(0x76);

	GameboyCore core;
	core.loadROM(code.rom());

	Time time{ 1, 2, 3, 0x1FF };
	auto time_provider = [&time]() {return time; };

	// Set the time provider for the test
	core.setTimeProvider(time_provider);

	// Latch time data by writing $00 and then $01 to $6000-$7FFF
	core.writeMemory(0x6000, 0x00);
	core.writeMemory(0x6000, 0x01);

	// Select seconds register
	core.writeMemory(0x4000, 0x08);
	EXPECT_EQ(core.readMemory(0xA000), 1);

	// Select minutes register
	core.writeMemory(0x4000, 0x09);
	EXPECT_EQ(core.readMemory(0xA000), 2);

	// Select hours register
	core.writeMemory(0x4000, 0x0A);
	EXPECT_EQ(core.readMemory(0xA000), 3);

	// Select days low register
	core.writeMemory(0x4000, 0x0B);
	EXPECT_EQ(core.readMemory(0xA000), 0xFF);

	// Select days high register
	core.writeMemory(0x4000, 0x0C);
	EXPECT_EQ(core.readMemory(0xA000), 0x01);
}