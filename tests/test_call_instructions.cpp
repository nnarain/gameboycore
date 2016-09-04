
#include <gtest/gtest.h>
#include "util/codegenerator.h"

#include <gameboy/gameboy.h>

using namespace gb;

static CPU::Status run(Gameboy& gameboy, std::vector<uint8_t>& rom)
{
	gameboy.loadROM(&rom[0], rom.size());

	while (!gameboy.isDone())
		gameboy.update();

	CPU::Status status = gameboy.getCPU().getStatus();

	gameboy.reset();

	return status;
}


TEST(CallInstructions, BaseCall)
{
	CodeGenerator code;
	code.block(
		0xCD, 0x50, 0x02	// CALL $250
	);
	code.address(0x250);
	code.block(0x76);

	Gameboy gameboy;
	const MMU& mmu = gameboy.getCPU().getMMU();
	CPU::Status status = run(gameboy, code.rom());

	EXPECT_EQ(status.pc.val, 0x251);
	EXPECT_EQ(status.sp.val, 0xFFFC);
	EXPECT_EQ(mmu.read(status.sp.val + 1), 0x01);
	EXPECT_EQ(mmu.read(status.sp.val + 0), 0x53);
}