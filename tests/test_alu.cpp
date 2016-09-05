
#include <gtest/gtest.h>

#include <gameboy/alu.h>
#include <gameboy/cpu.h>

using namespace gb;

TEST(ALUTests, AddHalfCarry)
{
	uint8_t flags = 0;
	ALU alu(flags);

	uint8_t a = 0x0F;
	alu.add(a, 1);

	EXPECT_EQ(a, 0x10);
	EXPECT_EQ(flags & CPU::Flags::H, CPU::Flags::H);
	EXPECT_EQ(flags & CPU::Flags::N, 0);
}

TEST(ALUTests, AddOverflow)
{
	uint8_t flags = 0;
	ALU alu(flags);

	uint8_t a = 0xFF;
	alu.add(a, 1);

	EXPECT_EQ(a, 0x00);
	EXPECT_EQ(flags & CPU::Flags::C, CPU::Flags::C);
	EXPECT_EQ(flags & CPU::Flags::Z, CPU::Flags::Z);
	EXPECT_EQ(flags & CPU::Flags::N, 0);
}

TEST(ALUTests, AddWithCarry)
{
	uint8_t flags = CPU::Flags::C;
	ALU alu(flags);

	uint8_t a = 0x16;
	alu.addc(a, 0x10);

	EXPECT_EQ(a, 0x27);
	EXPECT_EQ(flags & CPU::Flags::N, 0);
	EXPECT_EQ(flags & CPU::Flags::C, 0);
	EXPECT_EQ(flags & CPU::Flags::Z, 0);
}

TEST(ALUTests, Subtract)
{
	uint8_t flags = 0;
	ALU alu(flags);

	uint8_t a = 0x3E;
	alu.sub(a, 0x3E);

	EXPECT_EQ(a, 0x0);
	EXPECT_EQ(flags & CPU::Flags::N, CPU::Flags::N);
	EXPECT_EQ(flags & CPU::Flags::C, 0);
	EXPECT_EQ(flags & CPU::Flags::Z, CPU::Flags::Z);
}

TEST(ALUTests, SubtractHalfBorrow)
{
	uint8_t flags = 0;
	ALU alu(flags);

	uint8_t a = 0x3E;
	alu.sub(a, 0x0F);

	EXPECT_EQ(a, 0x2F);
	EXPECT_EQ(flags & CPU::Flags::N, CPU::Flags::N);
	EXPECT_EQ(flags & CPU::Flags::C, 0);
	EXPECT_EQ(flags & CPU::Flags::H, CPU::Flags::H);
}

TEST(ALUTests, SubtractFullBorrow)
{
	uint8_t flags = 0;
	ALU alu(flags);

	uint8_t a = 0x3E;
	alu.sub(a, 0x40);

	EXPECT_EQ(a, 0xFE);
	EXPECT_EQ(flags & CPU::Flags::N, CPU::Flags::N);
	EXPECT_EQ(flags & CPU::Flags::C, CPU::Flags::C);
}

TEST(ALUTests, SubtractWithBorrow)
{
	uint8_t flags = CPU::Flags::C;
	ALU alu(flags);

	uint8_t a = 0x3B;
	alu.subc(a, 0x2A);

	EXPECT_EQ(a, 0x10);
	EXPECT_EQ(flags & CPU::Flags::N, CPU::Flags::N);
	EXPECT_EQ(flags & CPU::Flags::C, 0);
}

TEST(ALUTests, SubtractWithBorrowHldBurrowAndFullBorrow)
{
	uint8_t flags = CPU::Flags::C;
	ALU alu(flags);

	uint8_t a = 0x3B;
	alu.subc(a, 0x4F);

	EXPECT_EQ(a, 0xEB);
	EXPECT_EQ(flags & CPU::Flags::N, CPU::Flags::N);
	EXPECT_EQ(flags & CPU::Flags::H, CPU::Flags::H);
	EXPECT_EQ(flags & CPU::Flags::C, CPU::Flags::C);
}