
/**
	\author Natesh Narain <nnaraindev@gmail.com>
*/

#include "test_helper.h"

gb::CPU::Status run(gb::Gameboy& gameboy, std::vector<uint8_t>& rom, bool reset, bool reload)
{
	if(reload)
		gameboy.loadROM(&rom[0], rom.size());

	do
	{
		gameboy.update();
	} while (!gameboy.isDone());

	gb::CPU::Status status = gameboy.getCPU().getStatus();

	if(reset)
		gameboy.reset();

	return status;
}
