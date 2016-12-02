
/**
	\file sound.h
	\brief Square wave generator
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
			\class Square
			\brief Square wave generator channels
			\ingroup Audio
		*/
		class Square : public Channel
		{
		public:
			static constexpr int LENGTH_MASK = 0x3F;

		public:

			Square(uint8_t& nrx1, uint8_t& nrx2, uint8_t& nrx3, uint8_t& nrx4, bool sweep = true) :
				Channel(nrx1, nrx2, nrx3, nrx4),
				has_sweep_(sweep)
			{
			}

			~Square()
			{
			}

		private:
			bool has_sweep_;
		};
	}
}

#endif // GAMEBOYCORE_SOUND_H
