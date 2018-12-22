#include <gtest/gtest.h>
#include <gameboycore/gameboycore.h>

#include "util/codegenerator.h"

using namespace gb;

TEST(MBC2, Lower4BitsInRAM)
{
    CodeGenerator code{ CodeGenerator::MBC::MBC2 };
    code.block(0x76);

    GameboyCore core;
    core.loadROM(code.rom());

    // Enable XRAM
    core.writeMemory(0x0000, 0x0A);

    // Write a value to external RAM, expect only the lower bits to be used
    core.writeMemory(0xA000, 0xDE);
    const auto value = core.readMemory(0xA000);

    EXPECT_EQ(value, 0x0E);
}

TEST(MBC2, BankSwapIgnoreUpper4)
{
    CodeGenerator code{ CodeGenerator::MBC::MBC2 };
    code.address(0x4000, 0x04);
    code.block(0xAA);
    code.address(0x4000, 0x05);
    code.block(0xBB);

    GameboyCore core;
    core.loadROM(code.rom());

    // Read value from the current bank
    const auto value1 = core.readMemory(0x4000);
    EXPECT_EQ(value1, 0x00);

    // Swap bank to $04
    core.writeMemory(0x2100, 0x04);
    const auto value2 = core.readMemory(0x4000);
    EXPECT_EQ(value2, 0xAA);

    // Swap to bank $05, but use value $F5 because the upper 4 bits are ignored
    core.writeMemory(0x2100, 0xF5);
    const auto value3 = core.readMemory(0x4000);
    EXPECT_EQ(value3, 0xBB);
}
