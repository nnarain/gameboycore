#ifndef GAMEBOYCORE_SOUND_H
#define GAMEBOYCORE_SOUND_H

#include "gameboycore/mmu.h"
#include "gameboycore/channel.h"

#include <cstdint>

namespace gb
{
	/**
		\class Sound
		\brief Wraps sound channels 1 and 2
	*/
	class Sound : public Channel
	{
	public:

		Sound(MMU::Ptr& mmu, uint16_t base, bool sweep = true) :
			Channel(mmu->get(base + 1), 0x3F),
			mmu_(mmu),
			has_sweep_(sweep)
		{
		}

		~Sound()
		{
		}

	private:
		MMU::Ptr& mmu_;
		bool has_sweep_;
	};
}

#endif // GAMEBOYCORE_SOUND_H
