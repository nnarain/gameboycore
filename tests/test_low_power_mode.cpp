
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
	Gameboy gameboy;

	CodeGenerator code;
	code.block(
		0x76 // halt
	);

	auto status = run(gameboy, code.rom());

	EXPECT_EQ(status.halt, true);
}

TEST(LowPowerTest, HaltResume)
{
	Gameboy gameboy;

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

	InterruptProvider interrupt{ gameboy.getCPU().getMMU(), InterruptProvider::Interrupt::VBLANK };

	auto status = run(gameboy, code.rom(), false);
	const auto& mmu = gameboy.getCPU().getMMU();

	EXPECT_EQ(status.halt, true);
	EXPECT_EQ(status.af.hi, 0x01);
	EXPECT_EQ(mmu.read(0xFFFF), 0x01);

	interrupt.set();
	status = run(gameboy, code.rom());

	EXPECT_EQ(status.af.hi, 0x50);
}