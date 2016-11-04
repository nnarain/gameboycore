/**
	\author Natesh Narain <nnaraindev@gmail.com>
	\date Nov 3 2016
*/


#ifndef GAMEBOY_APU_H
#define GAMEBOY_APU_H

#include "gameboy/mmu.h"
#include "gameboy/sound.h"
#include "gameboy/wave.h"
#include "gameboy/noise.h"

#include <memory>

namespace gb
{
	/**
		\brief Emulate Gameboy sound functions
	*/
	class APU
	{
	public:
		using Ptr = std::shared_ptr<APU>;

	public:

		APU(MMU::Ptr& mmu) : 
			mmu_(mmu),
			sound1_(mmu, memorymap::NR10_REGISTER),
			sound2_(mmu, memorymap::NR20_REGISTER),
			wave_(mmu),
			noise_(mmu)
		{
		}

		~APU()
		{
		}

	private:
		MMU::Ptr& mmu_;

		Sound sound1_;
		Sound sound2_;
		Wave wave_;
		Noise noise_;
	};
}

#endif
