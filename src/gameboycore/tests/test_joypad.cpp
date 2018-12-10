
#include <gtest/gtest.h>
#include "test_helper.h"
#include "bitutil.h"

#include <gameboycore/gameboycore.h>

using namespace gb;

TEST(Joypad, Idle)
{
    CodeGenerator code;
    // No key selection is made
    // Default value $0F is returned into A
    code.block(
        0x3E, 0x00, // LD A,10
        0xE0, 0x00, // LDH (00),A
        0xF0, 0x00, // LDH A,(00)
        0x76        // HALT
    );

    GameboyCore core;
    auto status = run(core, code.rom());

	EXPECT_EQ(status.a, 0x0F);
}

TEST(Joypad, Press)
{
    CodeGenerator code;
    
    code.block(
        0x3E, 0x10, // LD A,10     ; Select button group (A, B, SEL, START)
        0xE0, 0x00, // LDH (00),A  ; 
        0xF0, 0x00, // LDH A,(00)  ; Get buttons pressed
        0x76
    );

    GameboyCore core;

    auto& rom = code.rom();
    core.loadROM(&rom[0], rom.size());

    auto& joypad = core.getJoypad();
    joypad->press(Joy::Key::A);

    core.update(6);

    CPU::Status status = core.getCPU()->getStatus();
    uint8_t key_mask = bv(static_cast<uint8_t>(Joy::Key::A) >> 4);

    bool a_pressed = isClear(status.a, key_mask);

    EXPECT_TRUE(a_pressed);
}

TEST(Joypad, Press_AB)
{
    CodeGenerator code;
    // Attempt to write a value into the joypad register
    // The bit is held low 
    code.block(
        0x3E, 0x10, // LD A,10     ; Select button group (A, B, SEL, START)
        0xE0, 0x00, // LDH (00),A  ; 
        0xF0, 0x00, // LDH A,(00)  ; Get buttons pressed
        0x76
    );

    GameboyCore core;

    auto& rom = code.rom();
    core.loadROM(&rom[0], rom.size());

    auto& joypad = core.getJoypad();
    joypad->press(Joy::Key::A);
    joypad->press(Joy::Key::B);

    core.update(6);

    CPU::Status status = core.getCPU()->getStatus();
    uint8_t key_mask = bv(static_cast<uint8_t>(Joy::Key::A) >> 4) | bv(static_cast<uint8_t>(Joy::Key::B) >> 4);

    bool a_pressed = isClear(status.a, key_mask);

    EXPECT_TRUE(a_pressed);
}

TEST(Joypad, Release)
{
    CodeGenerator code;
    code.block(
        0x3E, 0x10, // LD A,10     ; Select button group (A, B, SEL, START)
        0xE0, 0x00, // LDH (00),A  ; 
        0xF0, 0x00, // LDH A,(00)  ; Get buttons pressed
        0x76
    );

    GameboyCore core;

    auto& rom = code.rom();
    core.loadROM(&rom[0], rom.size());

    auto& joypad = core.getJoypad();
    joypad->press(Joy::Key::A);
    joypad->release(Joy::Key::A);

    core.update(6);

    auto status = core.getCPU()->getStatus();

    uint8_t key_mask = bv(static_cast<uint8_t>(Joy::Key::A)) >> 4;
    EXPECT_EQ(status.a & key_mask, key_mask);
}