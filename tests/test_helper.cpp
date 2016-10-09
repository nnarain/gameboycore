
/**
	\author Natesh Narain <nnaraindev@gmail.com>
*/

#include "test_helper.h"

gb::CPU::Status run(gb::Gameboy& gameboy, std::vector<uint8_t>& rom, bool reset)
{
	gameboy.loadROM(&rom[0], rom.size());

	while (!gameboy.isDone())
		gameboy.update();

	gb::CPU::Status status = gameboy.getCPU().getStatus();

	if(reset)
		gameboy.reset();

	return status;
}
