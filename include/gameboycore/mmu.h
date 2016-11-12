/**
    \file mmu.h
    \author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef GAMEBOYCORE_MMU_H
#define GAMEBOYCORE_MMU_H

#include "gameboycore/mbc.h"
#include "gameboycore/cartinfo.h"

#include <vector>
#include <functional>
#include <array>
#include <cstdint>

namespace gb
{
    class MMU
    {
	public:
		using Ptr = std::shared_ptr<MMU>;

		using MemoryWriteHandler = std::function<void(uint8_t, uint16_t)>;
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

	private:
		void oamTransfer(uint8_t base);
		void loadResetValues();
		void initWriteMasks();

	private:
		MBC::Ptr mbc_;

		std::array<MemoryWriteHandler, 0x80> write_handlers_;
		std::array<MemoryReadHandler, 0x80>  read_handlers_;

		std::array<uint8_t, 0x80> apu_read_masks;
    };
}

#endif // GAMEBOY_MMU_H
