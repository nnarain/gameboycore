#include <cxxtest/TestSuite.h>
#include "util/codegenerator.h"

#include <gameboy/gameboy.h>

using namespace gb;

class LoadInstructionsTestSuite : public CxxTest::TestSuite
{
public:

	void testLoadImmediate()
	{
		// test load immediate for all registers

		CodeGenerator code;
		code.block(
			0x3E, 0x01, // LD A,1
			0x06, 0x02, // LD B,2
			0x0E, 0x03, // LD C,3
			0x16, 0x04, // LD D,4
			0x1E, 0x05, // LD E,5
			0x26, 0x06, // LD H,6
			0x2E, 0x07, // LD L,7

			0x76        // halt
		);

		
		Gameboy gameboy;

		auto rom = code.rom();
		gameboy.loadROM(&rom[0], rom.size());

		while (!gameboy.isDone())
			gameboy.update();

		CPU::Status status = gameboy.getCPU().getStatus();
		
		TS_ASSERT_EQUALS(status.af.hi, 1);
		TS_ASSERT_EQUALS(status.bc.hi, 2);
		TS_ASSERT_EQUALS(status.bc.lo, 3);
		TS_ASSERT_EQUALS(status.de.hi, 4);
		TS_ASSERT_EQUALS(status.de.lo, 5);
		TS_ASSERT_EQUALS(status.hl.hi, 6);
		TS_ASSERT_EQUALS(status.hl.lo, 7);
	}

private:
};
