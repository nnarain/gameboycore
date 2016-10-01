
/**
	@author Natesh Narain <nnaraindev@gmail.com>
*/

#include <gtest/gtest.h>
#include "test_helper.h"

using namespace gb;

static void testInvalidOpcode(uint8_t opcode)
{
	CodeGenerator code;
	code.block(
		opcode,
		0x76
	);

	Gameboy gameboy;
	(void)run(gameboy, code.rom());
}

TEST(TestInvalidOpcode, OpcodeD3)
{
	EXPECT_THROW({
		testInvalidOpcode(0xD3);
	}, std::runtime_error);
}

TEST(TestInvalidOpcode, OpcodeDB)
{
	EXPECT_THROW({
		testInvalidOpcode(0xDB);
	}, std::runtime_error);
}

TEST(TestInvalidOpcode, OpcodeDD)
{
	EXPECT_THROW({
		testInvalidOpcode(0xDD);
	}, std::runtime_error);
}

TEST(TestInvalidOpcode, OpcodeE3)
{
	EXPECT_THROW({
		testInvalidOpcode(0xE3);
	}, std::runtime_error);
}

TEST(TestInvalidOpcode, OpcodeE4)
{
	EXPECT_THROW({
		testInvalidOpcode(0xE4);
	}, std::runtime_error);
}

TEST(TestInvalidOpcode, OpcodeEB)
{
	EXPECT_THROW({
		testInvalidOpcode(0xEB);
	}, std::runtime_error);
}

TEST(TestInvalidOpcode, OpcodeEC)
{
	EXPECT_THROW({
		testInvalidOpcode(0xEC);
	}, std::runtime_error);
}

TEST(TestInvalidOpcode, OpcodeED)
{
	EXPECT_THROW({
		testInvalidOpcode(0xED);
	}, std::runtime_error);
}

TEST(TestInvalidOpcode, OpcodeF4)
{
	EXPECT_THROW({
		testInvalidOpcode(0xF4);
	}, std::runtime_error);
}

TEST(TestInvalidOpcode, OpcodeFC)
{
	EXPECT_THROW({
		testInvalidOpcode(0xFC);
	}, std::runtime_error);
}

TEST(TestInvalidOpcode, OpcodeFD)
{
	EXPECT_THROW({
		testInvalidOpcode(0xFD);
	}, std::runtime_error);
}