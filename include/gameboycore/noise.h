/**
	\author Natesh Narain <nnaraindev@gmail.com>
	\date   Nov 3 2016
*/

#ifndef GAMEBOYCORE_NOISE_H
#define GAMEBOYCORE_NOISE_H

#include "gameboycore/mmu.h"
#include "gameboycore/memorymap.h"

#include <cstdint>

namespace gb
{
	/**
		\class Noise
		\brief Generate white noise
	*/
	class Noise : public Channel
	{
	public:
		Noise(MMU::Ptr& mmu) :
			Channel(mmu->get(memorymap::NR41_REGISTER), 0x3F),
			mmu_(mmu),
			envelope_    (mmu->get(memorymap::NR42_REGISTER)),
			frequency_   (mmu->get(memorymap::NR43_REGISTER)),
			counter_     (mmu->get(memorymap::NR44_REGISTER))
		{
		}

		~Noise()
		{
		}

	private:
		MMU::Ptr& mmu_;

		uint8_t& envelope_;
		uint8_t& frequency_;
		uint8_t& counter_;
	};
}

#endif // GAMEBOY_NOISE_H
