#include <gtest/gtest.h>

#include "test_helper.h"
#include "util/codegenerator.h"

#include <gameboycore/gameboycore.h>

using namespace gb;

TEST(GPU, Scanline_VBlank)
{
    CodeGenerator code;
    // loop until line 144 -> blank
    code.block(
        0xF0, 0x44,       // LDH A, ($44)
        0xFE, 0x90,       // CP A, $90    -> CP A, 144
        0xC2, 0x50, 0x01, // JP NZ, $150
        0x76              // HALT
    );

    auto scanline = 0;
    auto vblank_fired = true;

    GameboyCore core;

    auto rom = code.rom();
    core.loadROM(&rom[0], rom.size());

    core.getGPU()->setVBlankCallback([&vblank_fired]() {
        vblank_fired = true;
    });
    core.getGPU()->setRenderCallback([&scanline](const GPU::Scanline&, int line) {
        scanline = line;
    });

    while (scanline < 143)
    {
        core.update(1);
    }

    EXPECT_TRUE(vblank_fired);
    EXPECT_EQ(scanline, 143);
}