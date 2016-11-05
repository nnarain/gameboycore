
/**
	\author Natesh Narain <nnaraindev@gmail.com>
	\date   Nov 5 2016
*/

#ifndef GAMEBOY_CHANNEL_H
#define GAMEBOY_CHANNEL_H

#include <cstdint>

namespace gb
{
	/**
		\class Channel
		\brief represents a Gameboy sound channel
	*/
	class Channel
	{
	public:
		Channel() :
			volume_unit_(0),
			timer_(0)
		{
		}

		/**
			Updated at 512 Hz
		*/
		void update()
		{
			timer_++;

			// 256 Hz
			if (timer_ % 2 == 0)
			{
			}

			// 128 Hz
			if (timer_ % 4 == 0)
			{
			}

			// 64 Hz
			if (timer_ % 8 == 0)
			{


				timer_ = 0;
			}
		}

		uint16_t getVolumeUnit() const
		{
			return volume_unit_;
		}

		~Channel()
		{
		}

	private:
		uint16_t volume_unit_;
		int timer_;
	};
}

#endif