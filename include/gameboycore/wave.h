
/**
	\author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef GAMEBOY_WAVE_H
#define GAMEBOY_WAVE_H

#include "gameboycore/mmu.h"
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
}

#endif // GAMEBOYCORE_WAVE_H
