#include <gtest/gtest.h>
#include <gameboycore/gameboycore.h>

#include "util/codegenerator.h"

using namespace gb;

TEST(MBC5, ReadDisabledXRAM)
{
    CodeGenerator code{ CodeGenerator::MBC::MBC5 };
    code.block(0x76);

    GameboyCore core;
    core.loadROM(code.rom());

    // XRAM is disabled by default, reading it will return 0xFF
    const auto value1 = core.readMemory(0xA000);
    const auto value2 = core.readMemory(0xBFFF);

    EXPECT_EQ(value1, 0xFF);
    EXPECT_EQ(value2, 0xFF);
}

TEST(MBC5, ReadEnabledXRAM)
{
    CodeGenerator code{ CodeGenerator::MBC::MBC5 };
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

TEST(MBC5, WriteEnabledXRAM)
{
    CodeGenerator code{ CodeGenerator::MBC::MBC5 };
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

TEST(MBC5, BankSwap)
{
    CodeGenerator code{ CodeGenerator::MBC::MBC5 };

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