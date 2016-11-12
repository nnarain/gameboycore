/**
    \file cpu.h
    \author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef GAMEBOYCORE_CPU_H
#define GAMEBOYCORE_CPU_H

// check endianness
#if !defined(__BIGENDIAN__) && !defined(__LITTLEENDIAN__)
#	error "Either __BIGENDIAN__ or __LITTLEENDIAN__ must be defined"
#endif

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
		union Register
		{
			struct {
#ifdef __LITTLEENDIAN__
				uint8_t lo;
				uint8_t hi;
#else
				uint8_t hi;
				uint8_t lo;
#endif
			};
			uint16_t val;
		};

		struct Status
		{
			Register af;
			Register bc;
			Register de;
			Register hl;
			Register sp;
			Register pc;
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
