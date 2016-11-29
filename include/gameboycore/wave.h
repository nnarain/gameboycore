
/**
	\author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef GAMEBOY_WAVE_H
#define GAMEBOY_WAVE_H

#include "gameboycore/channel.h"
#include "gameboycore/memorymap.h"

#include <cstdint>

namespace gb
{
	namespace detail
	{
		/**
			\class Wave
			\brief Wave register
			\ingroup Audio
		*/
		class Wave : public Channel
		{
		public:
			static const int LENGTH_MASK = 0xFF;

		public:
			Wave(uint8_t& nr30, uint8_t& nrx1, uint8_t& nrx2, uint8_t& nrx3, uint8_t& nrx4) :
				Channel(nrx1, nrx2, nrx3, nrx4),
				nr30_(nr30)
			{
			}

			virtual void trigger() override
			{
				if (length_counter_ == 0)
					length_counter_ = 256;

				Channel::trigger();
			}

			virtual bool isDacEnabled() const override
			{
				return (nr30_ & 0x80) != 0;
			}

			~Wave()
			{
			}

		private:
			uint8_t& nr30_;
		};
	}
}

#endif // GAMEBOYCORE_WAVE_H
