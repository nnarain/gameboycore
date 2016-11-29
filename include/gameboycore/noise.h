/**
	\author Natesh Narain <nnaraindev@gmail.com>
	\date   Nov 3 2016
*/

#ifndef GAMEBOYCORE_NOISE_H
#define GAMEBOYCORE_NOISE_H

#include "gameboycore/channel.h"

#include <cstdint>

namespace gb
{
	namespace detail
	{
		/**
			\class Noise
			\brief Generate white noise
			\ingroup Audio
		*/
		class Noise : public Channel
		{
		public:
			static constexpr int LENGTH_MASK = 0x3F;

		public:
			Noise(uint8_t& nrx1, uint8_t& nrx2, uint8_t nrx3, uint8_t& nrx4) :
				Channel(nrx1, nrx2, nrx3, nrx4)
			{
			}

			~Noise()
			{
			}

		private:
		};
	}
}

#endif // GAMEBOY_NOISE_H
