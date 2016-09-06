
#include <gtest/gtest.h>

#include "gameboy/cpu.h"
#include "shiftrotate.h"

using namespace gb;

TEST(Rotate, RotateLeft)
{
	uint8_t flags = 0;
	uint8_t a = 0x85;
	
	a = rotateLeft(a, flags);

	EXPECT_EQ(a, 0x0B);
	EXPECT_EQ(flags & CPU::Flags::C, CPU::Flags::C);
}

TEST(Rotate, RotateLeftThroughCarry)
{
	uint8_t flags = CPU::Flags::C;
	uint8_t a = 0x95;

	a = rotateLeftCarry(a, flags);

	EXPECT_EQ(a, 0x2B);
	EXPECT_EQ(flags & CPU::Flags::C, CPU::Flags::C);
}

TEST(Rotate, RotateRight)
{
	uint8_t flags = 0;
	uint8_t a = 0x81;

	a = rotateRight(a, flags);

	EXPECT_EQ(a, 0x40);
	EXPECT_EQ(flags & CPU::Flags::C, CPU::Flags::C);
}