
/**
	\author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef GAMEBOY_WAVE_H
#define GAMEBOY_WAVE_H

#include "gameboy/mmu.h"
#include "gameboy/memorymap.h"

#include <cstdint>

namespace gb
{
	/**
		\class Wave
		\brief Wave register
	*/
	class Wave : public Channel
	{
	public:
		Wave(MMU::Ptr& mmu) : 
			Channel(mmu->get(memorymap::NR31_REGISTER), 0xFF),
			mmu_(mmu)
		{
		}

		~Wave()
		{
		}

	private:
		MMU::Ptr& mmu_;
	};
}

#endif // GAMEBOY_WAVE_H
