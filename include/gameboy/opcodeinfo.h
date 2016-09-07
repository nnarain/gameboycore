
/**
	Define opcode metadata

	@author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef GAMEBOY_OPCODEINFO_H
#define GAMEBOY_OPCODEINFO_H

#include <stdint.h>

namespace gb
{
	/**
		Which page of instructions
	*/
	enum class OpcodePage
	{
		PAGE1, PAGE2
	};

	enum class OperandType
	{
		NONE,
		IMM8, // Immediate 8 bit integer
		IMM16 // Immediate 16 bit integer
	};

	/**
		Struct containing metadata
	*/
	struct OpcodeInfo
	{
		uint8_t cycles;
		const char *disassembly;
		OperandType operand_type;
	};

	OpcodeInfo getOpcodeInfo(uint8_t opcode, OpcodePage page);
}

#endif // GAMEBOY_OPCODEINFO_H
