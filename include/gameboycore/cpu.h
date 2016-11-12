/**
    \file cpu.h
    \author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef GAMEBOYCORE_CPU_H
#define GAMEBOYCORE_CPU_H

#include "gameboycore/mmu.h"
#include "gameboycore/gpu.h"
#include "gameboycore/apu.h"

#include <cstdint>
#include <memory>

namespace gb
{
    class GAMEBOYCORE_API CPU
    {
	public:

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
		};

		enum Flags
		{
			Z = 1 << 7,
			N = 1 << 6,
			H = 1 << 5,
			C = 1 << 4
		};

		using Ptr = std::unique_ptr<CPU>;

    public:
        CPU(const MMU::Ptr& mmu, const GPU::Ptr& gpu, const APU::Ptr& apu);
		~CPU();

        void step();

		void reset();

        bool isHalted() const;

		void setDebugMode(bool debug_mode);

		Status getStatus() const;

	private:
		class Impl;
		Impl* impl_;
    };
}

#endif // GAMEBOYCORE_CPU_H
