
#include <gtest/gtest.h>

#include "test_helper.h"
#include "util/codegenerator.h"


#include <gameboy/gameboy.h>

using namespace gb;


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

TEST(CallInstructions, ZFlag)
{
	CodeGenerator code;
	code.block(
		0x06, 0x01,			// LD B,1
		0x05,				// DEC B
		0xCC, 0x50, 0x02	// CALL Z,$250
	);
	code.address(0x250);
	code.block(0x76);

	Gameboy gameboy;
	const MMU& mmu = gameboy.getCPU().getMMU();
	CPU::Status status = run(gameboy, code.rom());

	EXPECT_EQ(status.af.lo & CPU::Flags::Z, CPU::Flags::Z);
	EXPECT_EQ(status.pc.val, 0x251);
	EXPECT_EQ(status.sp.val, 0xFFFC);
	EXPECT_EQ(mmu.read(status.sp.val + 1), 0x01);
	EXPECT_EQ(mmu.read(status.sp.val + 0), 0x56);

	code.reset();

	code.block(
		0xCC, 0x50, 0x02	// CALL Z,$250
	);
	code.address(0x250);
	code.block(0x76);

	status = run(gameboy, code.rom());

	EXPECT_EQ(status.af.lo & CPU::Flags::Z, 0);
	EXPECT_EQ(status.pc.val, 0x251);
	EXPECT_EQ(status.sp.val, 0xFFFE);
	EXPECT_EQ(mmu.read(status.sp.val + 1), 0x00);
	EXPECT_EQ(mmu.read(status.sp.val + 0), 0x00);
}

TEST(CallInstructions, CFlag)
{
	CodeGenerator code;
	code.block(
		0x37,
		0xDC, 0x50, 0x02	// CALL C,$250
	);
	code.address(0x250);
	code.block(0x76);

	Gameboy gameboy;
	const MMU& mmu = gameboy.getCPU().getMMU();
	CPU::Status status = run(gameboy, code.rom());

	EXPECT_EQ(status.af.lo & CPU::Flags::C, CPU::Flags::C);
	EXPECT_EQ(status.pc.val, 0x251);
	EXPECT_EQ(status.sp.val, 0xFFFC);
	EXPECT_EQ(mmu.read(status.sp.val + 1), 0x01);
	EXPECT_EQ(mmu.read(status.sp.val + 0), 0x54);

	code.reset();

	code.block(
		0xDC, 0x50, 0x02,	// CALL C,$250
		0x76
	);
	code.address(0x250);
	code.block(0x76);

	status = run(gameboy, code.rom());

	EXPECT_EQ(status.af.lo & CPU::Flags::C, 0);
	EXPECT_EQ(status.pc.val, 0x154);
	EXPECT_EQ(status.sp.val, 0xFFFE);
	EXPECT_EQ(mmu.read(status.sp.val + 1), 0x00);
	EXPECT_EQ(mmu.read(status.sp.val + 0), 0x00);
}

TEST(CallInstructions, Return)
{
	CodeGenerator code;
	code.block(
		0xCD, 0x50, 0x02,	// CALL $250
		0x76				// halt
	);
	code.address(0x250);
	code.block(
		0xC9				// RET
	);

	Gameboy gameboy;
	CPU::Status status = run(gameboy, code.rom());

	EXPECT_EQ(status.pc.val, 0x154);
	EXPECT_EQ(status.sp.val, 0xFFFE);
}
