
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
	EXPECT_EQ(flags & CPU::Flags::C, 0);
	EXPECT_EQ(flags & CPU::Flags::Z, 0);
}

TEST(ALUTests, AddOverflow)
{
	uint8_t flags = 0;
	ALU alu(flags);

	uint8_t a = 0xF0;
	alu.add(a, 0x10);

	EXPECT_EQ(a, 0x00);
	EXPECT_EQ(flags & CPU::Flags::C, CPU::Flags::C);
	EXPECT_EQ(flags & CPU::Flags::Z, CPU::Flags::Z);
	EXPECT_EQ(flags & CPU::Flags::H, 0);
	EXPECT_EQ(flags & CPU::Flags::N, 0);

	flags = 0;

	a = 0x3A;
	alu.add(a, 0xC6);

	EXPECT_EQ(a, 0x00);
	EXPECT_EQ(flags & CPU::Flags::C, CPU::Flags::C);
	EXPECT_EQ(flags & CPU::Flags::Z, CPU::Flags::Z);
	EXPECT_EQ(flags & CPU::Flags::H, CPU::Flags::H);
	EXPECT_EQ(flags & CPU::Flags::N, 0);
}

TEST(ALUTests, AddWithCarry)
{
	uint8_t flags = CPU::Flags::C;
	ALU alu(flags);

	uint8_t a = 0x6F;
	alu.addc(a, 0x10);

	EXPECT_EQ(a, 0x80);
	EXPECT_EQ(flags & CPU::Flags::C, 0);
	EXPECT_EQ(flags & CPU::Flags::Z, 0);
	EXPECT_EQ(flags & CPU::Flags::H, CPU::Flags::H);
	EXPECT_EQ(flags & CPU::Flags::N, 0);

	flags = CPU::Flags::C;

	a = 0xE1;
	alu.addc(a, 0x3B);

	EXPECT_EQ(a, 0x1D);
	EXPECT_EQ(flags & CPU::Flags::C, CPU::Flags::C);
	EXPECT_EQ(flags & CPU::Flags::Z, 0);
	EXPECT_EQ(flags & CPU::Flags::H, 0);
	EXPECT_EQ(flags & CPU::Flags::N, 0);
}

TEST(ALUTests, AddRelative)
{
	uint8_t flags = 0;
	ALU alu(flags);

	uint16_t sp = 0xFFF8;
	alu.addr(sp, 2);

	EXPECT_EQ(sp, 0xFFFA);
	EXPECT_EQ(flags & CPU::Flags::H, 0);
	EXPECT_EQ(flags & CPU::Flags::C, 0);
	EXPECT_EQ(flags & CPU::Flags::N, 0);

	flags = 0;
	sp = 0xFFF8;

	alu.addr(sp, -2);

	EXPECT_EQ(sp, 0xFFF6);
	EXPECT_EQ(flags & CPU::Flags::H, CPU::Flags::H);
	EXPECT_EQ(flags & CPU::Flags::C, CPU::Flags::C);
	EXPECT_EQ(flags & CPU::Flags::N, 0);
}

TEST(ALUTests, Add16bit)
{
	uint8_t flags = 0;
	ALU alu(flags);

	uint16_t hl = 0x8A23;
	alu.add(hl, 0x0605);

	EXPECT_EQ(hl, 0x9028);
	EXPECT_EQ(flags & CPU::Flags::N, 0);
	EXPECT_EQ(flags & CPU::Flags::H, CPU::Flags::H);
	EXPECT_EQ(flags & CPU::Flags::C, 0);

	flags = 0;
	hl = 0x8A23;
	alu.add(hl, 0x8A23);

	EXPECT_EQ(hl, 0x1446);
	EXPECT_EQ(flags & CPU::Flags::N, 0);
	EXPECT_EQ(flags & CPU::Flags::H, CPU::Flags::H);
	EXPECT_EQ(flags & CPU::Flags::C, CPU::Flags::C);
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
	EXPECT_EQ(flags & CPU::Flags::H, 0);
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

TEST(ALUTests, SubtractWithBorrowHalfBurrowAndFullBorrow)
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

TEST(ALUTests, AND)
{
	uint8_t flags = 0;
	ALU alu(flags);

	uint8_t a = 0x5A;
	alu.anda(a, 0x3F);

	EXPECT_EQ(a, 0x1A);
	EXPECT_EQ(flags & CPU::Flags::N, 0);
	EXPECT_EQ(flags & CPU::Flags::H, CPU::Flags::H);
	EXPECT_EQ(flags & CPU::Flags::C, 0);
}

TEST(ALUTests, ANDZero)
{
	uint8_t flags = 0;
	ALU alu(flags);

	uint8_t a = 0x5A;
	alu.anda(a, 0x00);

	EXPECT_EQ(a, 0x00);
	EXPECT_EQ(flags & CPU::Flags::Z, CPU::Flags::Z);
	EXPECT_EQ(flags & CPU::Flags::N, 0);
	EXPECT_EQ(flags & CPU::Flags::H, CPU::Flags::H);
	EXPECT_EQ(flags & CPU::Flags::C, 0);
}

TEST(ALUTests, OR)
{
	uint8_t flags = 0;
	ALU alu(flags);

	uint8_t a = 0x5A;
	alu.ora(a, 0x0F);

	EXPECT_EQ(a, 0x5F);
	EXPECT_EQ(flags & CPU::Flags::N, 0);
	EXPECT_EQ(flags & CPU::Flags::H, 0);
	EXPECT_EQ(flags & CPU::Flags::C, 0);
}

TEST(ALUTests, XOR)
{
	uint8_t flags = 0;
	ALU alu(flags);

	uint8_t a = 0xFF;
	alu.xora(a, 0xFF);

	EXPECT_EQ(a, 0x00);
	EXPECT_EQ(flags & CPU::Flags::Z, CPU::Flags::Z);
	EXPECT_EQ(flags & CPU::Flags::N, 0);
	EXPECT_EQ(flags & CPU::Flags::H, 0);
	EXPECT_EQ(flags & CPU::Flags::C, 0);
}

TEST(ALUTests, Compare)
{
	uint8_t flags = 0;
	ALU alu(flags);

	uint8_t a = 0x3C;
	alu.compare(a, 0x2F);

	EXPECT_EQ(flags & CPU::Flags::N, CPU::Flags::N);
	EXPECT_EQ(flags & CPU::Flags::H, CPU::Flags::H);
	EXPECT_EQ(flags & CPU::Flags::C, 0);
	EXPECT_EQ(flags & CPU::Flags::Z, 0);
}

TEST(ALUTests, CompareZero)
{
	uint8_t flags = 0;
	ALU alu(flags);

	uint8_t a = 0x3C;
	alu.compare(a, 0x3C);

	EXPECT_EQ(flags & CPU::Flags::N, CPU::Flags::N);
	EXPECT_EQ(flags & CPU::Flags::H, 0);
	EXPECT_EQ(flags & CPU::Flags::C, 0);
	EXPECT_EQ(flags & CPU::Flags::Z, CPU::Flags::Z);
}