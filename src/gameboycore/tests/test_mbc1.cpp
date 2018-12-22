
/**
	\author Natesh Narain <nnaraindev@gmail.com>
	\date   Oct 10 2016
*/

#include <gtest/gtest.h>

#include <gameboycore/gameboycore.h>

#include "util/codegenerator.h"

using namespace gb;

TEST(MBC1, ReadDisabledXRAM)
{
    CodeGenerator code{ CodeGenerator::MBC::MBC1 };
    code.block(0x76);

    GameboyCore core;
    core.loadROM(code.rom());

    // XRAM is disabled by default, reading it will return 0xFF
    const auto value1 = core.readMemory(0xA000);
    const auto value2 = core.readMemory(0xBFFF);

    EXPECT_EQ(value1, 0xFF);
    EXPECT_EQ(value2, 0xFF);
}

TEST(MBC1, ReadEnabledXRAM)
{
    CodeGenerator code{ CodeGenerator::MBC::MBC1 };
    code.block(0x76);

    GameboyCore core;
    core.loadROM(code.rom());

    // Enable XRAM
    core.writeMemory(0x1000, 0x0A);

    const auto value1 = core.readMemory(0xA000);
    const auto value2 = core.readMemory(0xBFFF);

    EXPECT_EQ(value1, 0x00);
    EXPECT_EQ(value2, 0x00);
}

TEST(MBC1, WriteEnabledXRAM)
{
    CodeGenerator code{ CodeGenerator::MBC::MBC1 };
    code.block(0x76);

    GameboyCore core;
    core.loadROM(code.rom());

    // Enable XRAM
    core.writeMemory(0x1000, 0x0A);

    // Write to XRAM
    core.writeMemory(0xA000, 0xDE);
    core.writeMemory(0xBFFF, 0xAD);

    const auto value1 = core.readMemory(0xA000);
    const auto value2 = core.readMemory(0xBFFF);

    EXPECT_EQ(value1, 0xDE);
    EXPECT_EQ(value2, 0xAD);
}

TEST(MBC1, BankSwap)
{
    CodeGenerator code{ CodeGenerator::MBC::MBC1 };

    // Write the value $DE in the first address in Bank $04
    code.address(0x4000, 0x04);
    code.block(0xDE);

    GameboyCore core;
    core.loadROM(code.rom());

    // Bank swap to Bank $04
    core.writeMemory(0x2000, 0x04);
    const auto value = core.readMemory(0x4000);

    EXPECT_EQ(value, 0xDE);
}

TEST(MBC1, BankRemap)
{
    /**
        Banks $20, $40 and $60 are remapped to $21, $41, $61
    */

    CodeGenerator code{ CodeGenerator::MBC::MBC1 };

    // Write values into remapped banks
    code.address(0x4000, 0x21);
    code.block(0xAA);

    code.address(0x4000, 0x41);
    code.block(0xBB);

    code.address(0x4000, 0x61);
    code.block(0xCC);

    GameboyCore core;
    core.loadROM(code.rom());

    // $4000 -> upper 2 bits
    // $2000 -> lower 5 bits

    // Swap to banks $20, $40 and $60, this will remap to $21, $41, $61 and read the first value

    // Bank swap to Bank $20
    core.writeMemory(0x4000, 0x01);
    core.writeMemory(0x2000, 0x00);
    const auto value1 = core.readMemory(0x4000);

    // Bank swap to Bank $40
    core.writeMemory(0x4000, 0x02);
    core.writeMemory(0x2000, 0x00);
    const auto value2 = core.readMemory(0x4000);

    // Bank swap to Bank $60
    core.writeMemory(0x4000, 0x03);
    core.writeMemory(0x2000, 0x00);
    const auto value3 = core.readMemory(0x4000);

    EXPECT_EQ(value1, 0xAA);
    EXPECT_EQ(value2, 0xBB);
    EXPECT_EQ(value3, 0xCC);
}
