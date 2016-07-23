/**
    \file mmu.h
    \author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef GAMEBOY_MMU_H
#define GAMEBOY_MMU_H

#include <vector>
#include <stdint.h>

namespace gb
{
    class MMU
    {
    private:
        std::vector<uint8_t> memory_;

    public:
        MMU();
        ~MMU();

        void load(uint8_t* rom, uint32_t size);

        uint8_t read(uint16_t);
        void write(uint8_t, uint16_t);
    };
}

#endif // GAMEBOY_MMU_H
