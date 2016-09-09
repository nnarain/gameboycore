
#include <gtest/gtest.h>

#include "gameboy/cpu.h"
#include "shiftrotate.h"

using namespace gb;

TEST(Rotate, RotateLeft)
{
	uint8_t flags = 0;
	uint8_t a = 0x85;
	
	a = rotateLeft(a, 1, flags);

	EXPECT_EQ(a, 0x0B);
	EXPECT_EQ(flags & CPU::Flags::C, CPU::Flags::C);
}

TEST(Rotate, RotateLeftThroughCarry)
{
	uint8_t flags = CPU::Flags::C;
	uint8_t a = 0x95;

	a = rotateLeftCarry(a, 1, flags);

	EXPECT_EQ(a, 0x2B);
	EXPECT_EQ(flags & CPU::Flags::C, CPU::Flags::C);
}

TEST(Rotate, RotateRight)
{
	uint8_t flags = 0;
	uint8_t a = 0x3B;

	a = rotateRight(a, 1, flags);

	EXPECT_EQ(a, 0x9D);
	EXPECT_EQ(flags & CPU::Flags::C, CPU::Flags::C);
}

TEST(Rotate, RotateRightThroughCarry)
{
	uint8_t flags = 0;
	uint8_t a = 0x81;

	a = rotateRightCarry(a, 1, flags);

	EXPECT_EQ(a, 0x40);
	EXPECT_EQ(flags & CPU::Flags::C, CPU::Flags::C);
}

TEST(Shift, Left)
{
	uint8_t flags = 0;
	uint8_t a = 0x80;

	a = shiftLeft(a, 1, flags);

	EXPECT_EQ(a, 0x00);
	EXPECT_EQ(flags & CPU::Flags::Z, CPU::Flags::Z);
	EXPECT_EQ(flags & CPU::Flags::C, CPU::Flags::C);
}

TEST(Shift, RightA)
{
	uint8_t flags = 0;
	uint8_t a = 0x8A;

	a = shiftRightA(a, 1, flags);

	EXPECT_EQ(a, 0xC5);
	EXPECT_EQ(flags & CPU::Flags::Z, 0);
	EXPECT_EQ(flags & CPU::Flags::C, 0);
}

TEST(Shift, RightL)
{
	uint8_t flags = 0;
	uint8_t a = 0x01;

	a = shiftRightL(a, 1, flags);

	EXPECT_EQ(a, 0x0);
	EXPECT_EQ(flags & CPU::Flags::Z, CPU::Flags::Z);
	EXPECT_EQ(flags & CPU::Flags::C, CPU::Flags::C);
}