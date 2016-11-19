/**
    \file mmu.h
    \brief Memory interface
    \author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef GAMEBOYCORE_MMU_H
#define GAMEBOYCORE_MMU_H

#include "gameboycore/gameboycore_api.h"

#include <functional>
#include <cstdint>
#include <memory>

namespace gb
{
    /**
        \class MMU
        \brief Memory interface
        \ingroup API
    */
    class GAMEBOYCORE_API MMU
    {
	public:
        //! Smart pointer type
		using Ptr = std::shared_ptr<MMU>;

		using MemoryWriteHandler = std::function<void(uint8_t, uint16_t)>;
		using MemoryReadHandler = std::function<uint8_t()>;

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
		class Impl;
		Impl* impl_;
    };
}

#endif // GAMEBOY_MMU_H
