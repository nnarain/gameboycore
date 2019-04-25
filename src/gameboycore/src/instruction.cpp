#include "gameboycore/instruction.h"
#include "gameboycore/opcodeinfo.h"

namespace gb
{
    std::string disassemble(const Instruction& instruction)
    {
        const auto opcode = instruction.opcode;
        const auto page = static_cast<OpcodePage>(instruction.page);

        const auto info = getOpcodeInfo(opcode, page);

        char buf[32];

        switch (info.userdata)
        {
        case OperandType::NONE:
            std::sprintf(buf, "%s", info.disassembly);
            break;
        case OperandType::IMM8:
            std::sprintf(buf, info.disassembly, instruction.operand_data[0]);
            break;
        case OperandType::IMM16:
            std::sprintf(buf, info.disassembly, instruction.operand_data[0], instruction.operand_data[1]);
            break;
        default:
            break;
        }

        return std::string(buf);
    }
}