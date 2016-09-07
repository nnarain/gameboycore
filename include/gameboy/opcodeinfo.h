
/**
	Define opcode metadata

	@author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef GAMEBOY_OPCODEINFO_H
#define GAMEBOY_OPCODEINFO_H

#include <stdint.h>

namespace gb
{

	struct OpcodeInfo
	{
		uint8_t cycles;
		const char *disassembly;
	};

	enum class OpcodePage
	{
		PAGE1, PAGE2
	};

	OpcodeInfo getOpcodeInfo(uint8_t opcode, OpcodePage page);
}

#endif // GAMEBOY_OPCODEINFO_H
