/**
    \file mmu.h
    \author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef GAMEBOY_MMU_H
#define GAMEBOY_MMU_H

#include <vector>
#include <stdint.h>

#include "gameboy/cartinfo.h"

namespace gb
{
    class MMU
    {
    private:
		using ROMBank = std::vector<uint8_t>;

        std::vector<uint8_t> memory_;
		std::vector<ROMBank> rom_banks_;

    public:
        MMU();
        ~MMU();

        void load(uint8_t* rom, uint32_t size);

        uint8_t read(uint16_t);
        void write(uint8_t, uint16_t);

	private:
		void loadROMBanks(uint8_t rom_size, uint8_t * rom);
		void copyROMToBanks(unsigned int num_banks, uint8_t* rom);
		
    };
}

#endif // GAMEBOY_MMU_H
