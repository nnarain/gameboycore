
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
		public:
			Channel(uint8_t& nrx4, uint8_t& nrx1, uint8_t length_mask) :
				nrx4_(nrx4),
				nrx1_(nrx1),
				length_mask_(length_mask),
				length_(0),
				enabled_(false)
			{
			}

			~Channel()
			{
			}

			virtual void restart()
			{
				enabled_ = true;
			}

			bool isEnabled() const
			{
				return enabled_;
			}

			uint8_t getLength() const
			{
				return length_;
			}

			void setLength(uint8_t l)
			{
				length_ = l;
			}

			void clockLength()
			{
				if (length_ > 0)
				{
					length_--;

					if (length_ == 0)
						enabled_ = false;
				}
			}

		private:
			bool isContinuous() const
			{
				return (nrx4_ & 0x40) == 0;
			}

		protected:
			//! NRx1 APU Register
			uint8_t& nrx1_;
			//! NRx4
			uint8_t& nrx4_;
			//! Length Data Mask
			const uint8_t length_mask_;

			//! Length Counter
			int length_;
			//! Channel Enabled flag
			bool enabled_;
		};
	}
}

#endif