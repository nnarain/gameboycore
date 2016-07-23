#include "gameboy/mmu.h"

namespace gb
{
    MMU::MMU()
    {
    }

    MMU::~MMU()
    {
    }

    void MMU::load(uint8_t* rom, uint32_t size)
    {
    }

    uint8_t MMU::read(uint16_t addr)
    {
        return memory_[addr];
    }

    void MMU::write(uint8_t value, uint16_t addr)
    {
        // TODO: implement ROM bank switching
        memory_[addr] = value;
    }
}
