/**
    \file cpu.h
    \author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef GAMEBOY_CPU_H
#define GAMEBOY_CPU_H

#include "gameboy/mmu.h"

namespace gb
{
    class CPU
    {
    private:
        MMU mmu_;
        bool halted_;

    public:
        CPU();

        void tick();
        bool isHalted();

        MMU& getMMU();
    };
}

#endif // GAMEBOY_CPU_H
