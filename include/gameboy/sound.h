#ifndef GAMEBOY_SOUND_H
#define GAMEBOY_SOUND_H

#include "gameboy/mmu.h"

#include <cstdint>

namespace gb
{
	/**
		\class Sound
		\brief Wraps sound channels 1 and 2
	*/
	class Sound
	{
	public:

		Sound(MMU::Ptr& mmu, uint16_t base) :
			mmu_(mmu)
		{
		}

		~Sound()
		{
		}

	private:
		MMU::Ptr& mmu_;
	};
}

#endif // GAMEBOY_SOUND_H
