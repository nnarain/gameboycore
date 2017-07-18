
/**
	\author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef GAMEBOY_WAVE_H
#define GAMEBOY_WAVE_H

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
		class WaveChannel
		{
		public:
			static const int LENGTH_MASK = 0xFF;

		public:
			WaveChannel()
			{
			}

			~WaveChannel()
			{
			}

		private:
			
		};
	}
}

#endif // GAMEBOYCORE_WAVE_H
