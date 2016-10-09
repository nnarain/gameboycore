
/**
	\author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef TEST_HELPER_H
#define TEST_HELPER_H

#include <gameboy/gameboy.h>

#include <vector>

#include "util/codegenerator.h"

gb::CPU::Status run(gb::Gameboy& gameboy, std::vector<uint8_t>& rom, bool reset = true);

#endif // TEST_HELPER_H
