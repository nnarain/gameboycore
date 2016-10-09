
#include <gtest/gtest.h>
#include "test_helper.h"
#include "bitutil.h"

using namespace gb;

TEST(Joypad, Idle)
{
	Gameboy gameboy;
	Joypad joypad = gameboy.getJoypad();
	const MMU& mmu = gameboy.getCPU().getMMU();

	EXPECT_EQ(mmu.read(memorymap::JOYPAD_REGISTER), 0xFF);
}

TEST(Joypad, Press)
{
	Gameboy gameboy;
	Joypad joypad = gameboy.getJoypad();
	const MMU& mmu = gameboy.getCPU().getMMU();

	CodeGenerator code;
	code.block(
		0x3E, 0x10, // LD A,10
		0xE0, 0x00, // LDH (00),A
		0xF0, 0x00, // LDH A,(00)
		0x76
	);

	joypad.press(Joypad::Key::A);

	auto status = run(gameboy, code.rom(), false);

	uint8_t key_mask = BV(static_cast<uint8_t>(Joypad::Key::A)) >> 4;
	EXPECT_EQ(status.af.hi & key_mask, 0);
}

TEST(Joypad, Release)
{
	Gameboy gameboy;
	Joypad joypad = gameboy.getJoypad();

	CodeGenerator code;
	code.block(
		0x3E, 0x10, // LD A,01
		0xE0, 0x00, // LDH (00), A
		0xF0, 0x00, // LDH A,(00)
		0x76
	);

	joypad.press(Joypad::Key::A);
	joypad.release(Joypad::Key::A);

	auto status = run(gameboy, code.rom(), false);

	uint8_t key_mask = BV(static_cast<uint8_t>(Joypad::Key::A)) >> 4;
	EXPECT_EQ(status.af.hi & key_mask, key_mask);
}