/**
    \file mmu.h
    \author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef GAMEBOY_MMU_H
#define GAMEBOY_MMU_H

#include <vector>
#include <cstdint>
#include <functional>
#include <map>

#include "gameboy/cartinfo.h"

namespace gb
{
    class MMU
    {
	public:
		using MemoryWriteHandler = std::function<void(uint8_t)>;
		using MemoryReadHandler = std::function<uint8_t()>;

    private:
		using ROMBank = std::vector<uint8_t>;

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
		uint8_t read(uint16_t);
		/**
			Write a byte to the specified location
		*/
        void write(uint8_t value, uint16_t addr);
		/**
			Write a word to the specified location
		*/
		void write(uint16_t value, uint16_t addr);

		/**
			
		*/
		void addWriteHandler(uint16_t addr, MemoryWriteHandler handler);

		void addReadHandler(uint16_t addr, MemoryReadHandler handler);

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

	private:

		std::vector<uint8_t> memory_;
		std::vector<ROMBank> rom_banks_;

		std::map<uint16_t, MemoryWriteHandler> write_handlers_;
		std::map<uint16_t, MemoryReadHandler>  read_handlers_;
		
    };
}

#endif // GAMEBOY_MMU_H
