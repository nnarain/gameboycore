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
