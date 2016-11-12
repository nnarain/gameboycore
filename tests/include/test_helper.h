
/**
	\author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef TEST_HELPER_H
#define TEST_HELPER_H

#include <gameboycore/gameboycore.h>

#include <vector>

#include "util/codegenerator.h"

gb::CPU::Status run(gb::GameboyCore& gameboy, std::vector<uint8_t>& rom, bool reset = true, bool reload = true);

#endif // TEST_HELPER_H
