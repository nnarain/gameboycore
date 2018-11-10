/**
    \file cpu.h
    \brief Gameboy CPU
    \author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef GAMEBOYCORE_CPU_H
#define GAMEBOYCORE_CPU_H

#include "gameboycore/mmu.h"
#include "gameboycore/gpu.h"
#include "gameboycore/apu.h"
#include "gameboycore/link.h"

#include <cstdint>
#include <memory>
#include <functional>
#include <string>

namespace gb
{
    /*!
        \class CPU
        \brief Emulates Gameboy CPU instructions
        \ingroup API
    */
    class GAMEBOYCORE_API CPU
    {
	public:
        //! CPU state
		struct Status
		{
			uint16_t af;
			uint8_t a;
			uint8_t f;

			uint16_t bc;
			uint8_t b;
			uint8_t c;

			uint16_t de;
			uint8_t d;
			uint8_t e;

			uint16_t hl;
			uint8_t h;
			uint8_t l;

			uint16_t pc;
			uint16_t sp;

			bool halt;
			bool stopped;
			bool ime;
			uint8_t enabled_interrupts;
		};

        //! Flags set by the most recent instruction
		enum Flags
		{
			Z = 1 << 7,
			N = 1 << 6,
			H = 1 << 5,
			C = 1 << 4
		};

        //! Smart pointer type
		typedef std::unique_ptr<CPU> Ptr;

    public:
        CPU(MMU::Ptr& mmu, GPU::Ptr& gpu, APU::Ptr& apu, Link::Ptr& link);
		CPU(const CPU&) = delete;
		~CPU();

        /**
            Run one CPU fetch, decode, execute cycle
        */
        void step();

        /**
            Reset the CPU state
        */
		void reset();

        /**
            \return true if the CPU is halted
        */
        bool isHalted() const;

        /**
            Set CPU debug mode
        */
		void setDebugMode(bool debug_mode);

		/**
			Set a callback function for the disassembly string when the CPU is in debug mode
		*/
		void setDisassemblyCallback(std::function<void(const std::string&)>);

        /**
            Get the current status of the CPU
        */
		Status getStatus() const;

	private:
        // Private implementation class
		class Impl;
		Impl* impl_;
    };
}

#endif // GAMEBOYCORE_CPU_H
