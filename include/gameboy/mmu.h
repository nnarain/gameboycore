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
		MMU(const MMU&) = delete;
        ~MMU();

		/**
			Load memory
		*/
        void load(uint8_t* rom, uint32_t size);

		/**
			@return the value of memory at the psecified location
		*/
        uint8_t read(uint16_t) const;
		/**
			Write a byte to the specified location
		*/
        void write(uint8_t value, uint16_t addr);
		/**
			Write a word to the specified location
		*/
		void write(uint16_t value, uint16_t addr);

		/**
			@return a reference to a memory location
		*/
		uint8_t& get(uint16_t);

		/**
		*/
		uint8_t* getptr(uint16_t);

		unsigned int numBanks() const;

	private:
		void loadROMBanks(uint8_t rom_size, uint8_t * rom);
		void copyROMToBanks(unsigned int num_banks, uint8_t* rom);

		void oamTransfer(uint8_t base);
		
    };
}

#endif // GAMEBOY_MMU_H
