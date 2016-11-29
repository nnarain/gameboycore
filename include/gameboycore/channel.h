
/**
	\file channel.h
	\brief Base class for Sound channel
	\author Natesh Narain <nnaraindev@gmail.com>
	\date   Nov 5 2016
*/

#ifndef GAMEBOYCORE_CHANNEL_H
#define GAMEBOYCORE_CHANNEL_H

#include <cstdint>

namespace gb
{
	namespace detail
	{
		/**
			\class Channel
			\brief Base class for Sound channel
			\ingroup Audio
		*/
		class Channel
		{
			//! Mask covers DAC bits
			static constexpr int DAC_MASK = 0xF8;

		public:
			Channel(uint8_t& nrx1, uint8_t& nrx2, uint8_t& nrx3, uint8_t& nrx4) :
				nrx1_(nrx1),
				nrx2_(nrx2),
				nrx3_(nrx3),
				nrx4_(nrx4),
				length_(0),
				enabled_(false),
				dac_power_(0xF)
			{
			}

			~Channel()
			{
			}

			virtual void trigger()
			{
				// only enable channel if the DAC is on
				if(isDacEnabled())
					enabled_ = true;

				if (length_ == 0)
					length_ = 64;
			}

			bool isEnabled() const
			{
				return enabled_;
			}

			uint8_t getLength() const
			{
				return length_;
			}

			void setLength(int length)
			{
				length_ = length;
			}

			void setDacPower(uint8_t p)
			{
			//	dac_power_ = (p & 0x0F);

				if (p == 0)
					enabled_ = false;
			}

			virtual bool isDacEnabled() const
			{
				return (nrx2_ & DAC_MASK) != 0;
			}

			void clockLength()
			{
				if (!isCounterMode()) return;

				if (length_ > 0)
				{
					length_--;
				}

				if (length_ == 0)
					enabled_ = false;
			}

		private:
			bool isCounterMode()
			{
				return (nrx4_ & 0x40) != 0;
			}

		protected:
			//! NRx1 APU Register
			uint8_t& nrx1_;
			//! NRx2 APU Register
			uint8_t& nrx2_;
			//! NRx3 APU Register
			uint8_t& nrx3_;
			//! NRx4 APU Register
			uint8_t& nrx4_;

			//! Length Counter
			int length_;
			//! Channel Enabled flag
			bool enabled_;

			//! DAC output power
			uint8_t dac_power_;
		};
	}
}

#endif