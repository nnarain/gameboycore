/**
 * \file instruction.h
 * \author Natesh Narain <nnaraindev@gmail.com>
 * \date April 21 2019
*/

#ifndef GAMEBOYCORE_INSTRUCTION_H
#define GAMEBOYCORE_INSTRUCTION_H

#include <array>
#include <cstdint>

namespace gb
{
    struct Instruction
    {
		enum class OpcodePage
		{
			PAGE1,
			PAGE2
		};

        //! Instruction Opcode
        uint8_t opcode;
		//! Opcode Page
		OpcodePage page;
        //! Opcode Data
        std::array<uint8_t, 2> operand_data;

        Instruction(uint8_t opcode, OpcodePage page, std::array<uint8_t, 2> data)
            : opcode{opcode}
			, page{page}
            , operand_data{data}
        {
        }
    };
}

#endif // GAMEBOYCORE_INSTRUCTION_H
