#include <gtest/gtest.h>

#include "test_helper.h"
#include "util/codegenerator.h"

#include <gameboycore/gameboycore.h>
#include <gameboycore/memorymap.h>

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

TEST(API, SpriteAttributes)
{
    /**
        OAM Registers - 4 bytes per sprite

        0 - y coord
        1 - x coord
        2 - CHR code (tile number)
        3 - Attributes
            Bits:
                7     - Priority
                6     - Vertical flip
                5     - Horizontal flip
                4     - DMG palette
                3     - CBG character bank
                2,1,0 - CGB palette
    */

    CodeGenerator code;
    code.block(
        0x3E, 0x82,      // LD A, $02 -> LCDC enable | sprites enabled
        0xE0, 0x40,      // LDH ($40), A
        0xC3, 0x54, 0x01 // JP $0154
    );

    // initialize the core
    GameboyCore core;

    auto rom = code.rom();
    core.loadROM(&rom[0], rom.size());

    // write sprites into memory
    core.writeMemory(memorymap::OAM_START + 0, 8);
    core.writeMemory(memorymap::OAM_START + 1, 8);
    core.writeMemory(memorymap::OAM_START + 2, 1);
    core.writeMemory(memorymap::OAM_START + 3, 0x20); // horizontal flip

    core.writeMemory(memorymap::OAM_START + 4, 0);
    core.writeMemory(memorymap::OAM_START + 5, 0);
    core.writeMemory(memorymap::OAM_START + 6, 2);
    core.writeMemory(memorymap::OAM_START + 7, 0x40); // vertical flip

    core.writeMemory(memorymap::OAM_START + 8, 0);
    core.writeMemory(memorymap::OAM_START + 9, 0);
    core.writeMemory(memorymap::OAM_START + 10, 3);
    core.writeMemory(memorymap::OAM_START + 11, 0x80); // display priority

    core.writeMemory(memorymap::OAM_START + 12, 0);
    core.writeMemory(memorymap::OAM_START + 13, 0);
    core.writeMemory(memorymap::OAM_START + 14, 0);
    core.writeMemory(memorymap::OAM_START + 15, 0x07); // CGB palette 7

    core.writeMemory(memorymap::OAM_START + 16, 0);
    core.writeMemory(memorymap::OAM_START + 17, 0);
    core.writeMemory(memorymap::OAM_START + 18, 0);
    core.writeMemory(memorymap::OAM_START + 19, 0x10); // DMG palette

    // emulate a frame to populate sprite cache
    core.emulateFrame();

    // get sprites
    auto sprites = core.getGPU()->getSpriteCache();

    const auto& s0 = sprites[0];
    const auto& s1 = sprites[1];
    const auto& s2 = sprites[2];
    const auto& s3 = sprites[3];
    const auto& s4 = sprites[4];

    EXPECT_EQ(s0.x, 8);
    EXPECT_EQ(s0.y, 8);
    EXPECT_EQ(s0.tile, 1);
    EXPECT_EQ(s0.isHorizontallyFlipped(), true);
    EXPECT_EQ(s0.isVerticallyFlipped(), false);

    EXPECT_EQ(s1.isHorizontallyFlipped(), false);
    EXPECT_EQ(s1.isVerticallyFlipped(), true);

    EXPECT_EQ(!s2.hasPriority(), true);

    EXPECT_EQ(s3.getCgbPalette(), 0x07);

    EXPECT_EQ(s4.paletteOBP0(), 1);
}