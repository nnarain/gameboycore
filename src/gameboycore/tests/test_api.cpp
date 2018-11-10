#include <gtest/gtest.h>

#include "test_helper.h"
#include "util/codegenerator.h"

#include <gameboycore/gameboycore.h>

using namespace gb;

TEST(API, SetBeforeLoad)
{
    CodeGenerator code;
    code.block(
        0xF0, 0x44,       // LDH A, ($44)
        0xFE, 0x90,       // CP A, $90    -> CP A, 144
        0xC2, 0x50, 0x01, // JP NZ, $150
        0x76              // HALT
    );

    GameboyCore core;

    bool vblank_fired = false;
    core.setVBlankCallback([&vblank_fired](){ vblank_fired = true; });

    auto rom = code.rom();
    core.loadROM(&rom[0], rom.size());

    core.emulateFrame();

    EXPECT_TRUE(vblank_fired);
}

TEST(API, CallbackAfterReset)
{
    CodeGenerator code;
    code.block(
        0xF0, 0x44,       // LDH A, ($44)
        0xFE, 0x90,       // CP A, $90    -> CP A, 144
        0xC2, 0x50, 0x01, // JP NZ, $150
        0x76              // HALT
    );

    GameboyCore core;

    bool vblank_fired = false;
    core.setVBlankCallback([&vblank_fired]() { vblank_fired = true; });

    auto rom = code.rom();
    core.loadROM(&rom[0], rom.size());

    core.emulateFrame();

    EXPECT_TRUE(vblank_fired);

    // run again to show the callback stays after a core reset
    core.loadROM(&rom[0], rom.size());

    core.emulateFrame();

    EXPECT_TRUE(vblank_fired);
}