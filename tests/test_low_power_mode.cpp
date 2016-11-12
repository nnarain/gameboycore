
/**
	\author Natesh Narain <nnaraindev@gmail.com>
	\date Oct 9 2016
*/

#include <gtest/gtest.h>
#include "test_helper.h"

#include <iostream>

using namespace gb;

TEST(LowPowerTest, Halt)
{
	GameboyCore gameboy;

	CodeGenerator code;
	code.block(
		0x76 // halt
	);

	auto status = run(gameboy, code.rom());

	EXPECT_EQ(status.halt, true);
}

TEST(LowPowerTest, HaltResume)
{
	GameboyCore gameboy;

	CodeGenerator code;
	code.block(
		0xFB,			// EI
		0x3E, 0x01,		// LD A,$01
		0xE0, 0xFF,		// LDH (FF),A ; enable vblank interrupt
		0x76,			// halt
		0x3E, 0x50,		// LD A,$50
		0x76			// halt
	);
	// vblank interrupt handler
	code.address(0x40);
	code.block(
		0x3E, 0x50,
		0x76
	);

	auto status = run(gameboy, code.rom(), false);
	InterruptProvider interrupt{ *gameboy.getMMU(), InterruptProvider::Interrupt::VBLANK };
	auto mmu = gameboy.getMMU();

	EXPECT_EQ(status.halt, true);
	EXPECT_EQ(status.af.hi, 0x01);
	EXPECT_EQ(mmu->read(0xFFFF), 0x01);

	interrupt.set();
	status = run(gameboy, code.rom(), true, false);

	EXPECT_EQ(status.af.hi, 0x50);
}

TEST(LowPowerTest, Stop)
{
	GameboyCore gameboy;

	CodeGenerator code;
	code.block(
		0x10, 0x00, // stop
		0x76
	);

	auto status = run(gameboy, code.rom());

	EXPECT_EQ(status.stopped, true);
	EXPECT_EQ(status.halt, true);
}

TEST(LowPowerTest, StopResume)
{
	CodeGenerator code;
	code.block(
		0xFB,			// EI
		0x3E, 0x10,		// LD A,$10
		0xE0, 0xFF,		// LDH (FF),A ; enable joypad interrupt
		0x10, 0x00,		// stop
		0x3E, 0x50,		// LD A,$50
		0x76			// halt
	);
	// joypad interrupt handler
	code.address(0x60);
	code.block(
		0x3E, 0x50,
		0x76
	);

	
	GameboyCore gameboy;

	auto status = run(gameboy, code.rom(), false);
	InterruptProvider interrupt{ *gameboy.getMMU(), InterruptProvider::Interrupt::JOYPAD };
	auto mmu = gameboy.getMMU();

	EXPECT_EQ(status.halt, true);
	EXPECT_EQ(status.stopped, true);
	EXPECT_EQ(status.af.hi, 0x10);
	EXPECT_EQ(mmu->read(0xFFFF), 0x10);

	interrupt.set();
	status = run(gameboy, code.rom(), true, false);

	EXPECT_EQ(status.af.hi, 0x50);
}