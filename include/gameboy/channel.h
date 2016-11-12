
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
		Channel(uint8_t& length_counter, uint8_t length_mask) :
			length_counter_(length_counter),
			length_mask_(length_mask),
			volume_unit_(0),
			timer_(0),
			enabled_(false)
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
				lengthCounterTick();
			}

			// 128 Hz
			if (timer_ % 4 == 0)
			{
			}

			// 64 Hz
			if (timer_ % 8 == 0)
			{

				// update volume unit

				timer_ = 0;
			}
		}

		uint16_t getVolumeUnit() const
		{
			return volume_unit_;
		}

		bool isEnabled() const
		{
			return enabled_;
		}

		~Channel()
		{
		}

	private:

		void lengthCounterTick()
		{
			auto value = length_counter_ & length_mask_;
			value--;

			if (value == 0)
			{
				enabled_ = false;
			}

			length_counter_ = (length_counter_ & ~length_mask_) | value;
		}

	private:
		uint8_t& length_counter_;
		uint8_t length_mask_;
		uint16_t volume_unit_;
		int timer_;
		bool enabled_;
	};
}

#endif