
/**
	\file sound.h
	\author Natesh Narain <nnaraindev@gmail.com>
	\date Nov 21 2016
*/

#ifndef GAMEBOYCORE_SOUND_H
#define GAMEBOYCORE_SOUND_H

#include "gameboycore/mmu.h"
#include "gameboycore/channel.h"

#include <cstdint>

namespace gb
{
	namespace detail
	{
		/**
			\class Sound
			\brief Wraps sound channels 1 and 2
			\ingroup Audio
		*/
		class Sound : public Channel
		{
		public:

			Sound(uint8_t& length_counter, bool sweep = true) :
				Channel(length_counter, 0x3F),
				has_sweep_(sweep)
			{
			}

			~Sound()
			{
			}

		private:
			bool has_sweep_;
		};
	}
}

#endif // GAMEBOYCORE_SOUND_H
