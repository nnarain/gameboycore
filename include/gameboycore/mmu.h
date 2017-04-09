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
#include <vector>

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
		typedef std::unique_ptr<MMU> Ptr;

		typedef std::function<void(uint8_t, uint16_t)> MemoryWriteHandler;
		typedef std::function<uint8_t(uint16_t)>       MemoryReadHandler;

    public:
        MMU(uint8_t* rom, uint32_t size);
		MMU(const MMU&) = delete;
        ~MMU();

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
		uint8_t readVram(uint16_t addr, uint8_t bank);

		/**
			tranfer `n` bytes from `src` to `dest`
		*/
		void dma(uint16_t dest, uint16_t src, uint16_t n);

		/**
			Add a IO write handler

			\param addr IO address
			\handler the handler
		*/
		void addWriteHandler(uint16_t addr, MemoryWriteHandler handler);

		/**
			Add an IO read handler

			\param addr IO address
			\param handler the handler
		*/
		void addReadHandler(uint16_t addr, MemoryReadHandler handler);

		/**
			\return Battery RAM
		*/
		std::vector<uint8_t> getBatteryRam() const;

		/**
			Set battery RAM

			\param buffer containing battery RAM
		*/
		void setBatteryRam(const std::vector<uint8_t>& battery_ram);

		/**
			Check if OAM transfer has occured
		*/
		bool getOamTransferStatus() const;

		/**
			@return true if rom is CGB compatible
		*/
		bool cgbEnabled() const;

		/**
			\return a reference to a memory location
		*/
		uint8_t& get(uint16_t);

		/**
			\return point to memory location
		*/
		uint8_t* getptr(uint16_t);

	private:
		class Impl;
		Impl* impl_;
    };
}

#endif // GAMEBOY_MMU_H
