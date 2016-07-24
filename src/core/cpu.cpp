
#include "gameboy/cpu.h"

namespace gb
{
    CPU::CPU() :
        mmu_(),
        halted_(false)
    {
    }

    void CPU::tick()
    {
    }

    bool CPU::isHalted()
    {
        return halted_;
    }

    MMU& CPU::getMMU()
    {
        return mmu_;
    }
}
