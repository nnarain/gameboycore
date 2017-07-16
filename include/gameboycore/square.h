
/**
	\file square.h
	\brief Square wave generator
	\author Natesh Narain <nnaraindev@gmail.com>
	\date Nov 21 2016
*/

#ifndef GAMEBOYCORE_SOUND_H
#define GAMEBOYCORE_SOUND_H

#include "gameboycore/mmu.h"

#include <array>
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
		class Square
		{
		public:
			static constexpr int LENGTH_MASK = 0x3F;
			static constexpr int DAC_MASK = 0xF8;

		public:

			Square(bool sweep = true) :
				duty_(0),
				is_enabled_(false),
				waveform_idx_(0),
				length_counter_(0),
				envelop_period_(0),
				volume_counter_(0)
			{
				// waveforms with different duty cycles
				waveform_[0] = { 0, 0, 0, 0, 0, 0, 0, 1 };
				waveform_[1] = { 1, 0, 0, 0, 0, 0, 0, 1 };
				waveform_[2] = { 1, 0, 0, 0, 0, 1, 1, 1 };
				waveform_[3] = { 0, 1, 1, 1, 1, 1, 1, 0 };
			}

			~Square()
			{
			}

			void step()
			{
				// clock the waveform timer
				if (waveform_timer_-- <= 0)
				{
					// reset timer
					waveform_timer_ = calculateWaveformTimer();

					// next waveform value
					waveform_idx_ = (waveform_idx_ + 1) % waveform_[0].size();
				}

				// compute the output volume
				// volume is zero if not enabled
				if (isEnabled() && dac_enabled_)
				{
					output_volume_ = volume_counter_;
				}
				else
				{
					output_volume_ = 0;
				}

				// output is low if the waveform is low
				if (waveform_[duty_][waveform_idx_] == 0)
				{
					output_volume_ = 0;
				}
			}

			void clockLength()
			{
				if (length_enabled_ && length_counter_ > 0)
				{
					// decrement the length counter and disable the channel when it reaches zero
					if (length_counter_-- == 0)
					{
						is_enabled_ = false;
					}
				}
			}

			void clockVolume()
			{
				// clock the envelop timer
				if (envelop_timer_-- <= 0)
				{
					// reset envelop timer
					envelop_timer_ = envelop_period_;

					if (envelop_period_ != 0)
					{
						if (envelope_add_mode_ && volume_counter_ < 15)
						{
							volume_counter_++;
						}
						else if (!envelope_add_mode_ && volume_counter_ > 0)
						{
							volume_counter_--;
						}
					}
				}
			}

			uint8_t read(uint16_t register_number)
			{
				// deconstruct byte value into variables

				switch (register_number)
				{
				case 0:
					if (has_sweep_)
					{
						return 0;
					}
					else
					{
						return ((sweep_period_ & 0x07) << 4) | (negate_ << 3) | (shift_ & 0x07);
					}
				case 1:
					return ((duty_ & 0x03) << 6) | (length_ & 0x3F);
				case 2:
					return ((volume_ & 0x0F) << 4) | (envelope_add_mode_ << 3) | (envelop_period_ & 0x07);
				case 3:
					return frequency_ & 0x00FF;
				case 4:
					return ((frequency_ & 0x0700) >> 8) | (trigger_ << 7) | (length_enabled_ << 6);
				}
			}

			void write(uint8_t value, uint16_t register_number)
			{
				// construct byte values from variables

				switch (register_number)
				{
				case 0:
					if (has_sweep_)
					{
						sweep_period_ = (value & 0x70) >> 4;
						negate_ = (value & 0x08) != 0;
						shift_ = value & 0x07;
					}
					break;
				case 1:
					duty_ = (value >> 6);
					length_ = (value & 0x3F);
					length_counter_ = 64 - length_;
					break;
				case 2:
					volume_ = (value >> 4);
					envelope_add_mode_ = (value & 0x08) != 0;
					envelop_period_ = (value & 0x07);

					dac_enabled_ = (value & DAC_MASK) != 0;
					volume_counter_ = volume_;
					envelop_timer_ = envelop_period_;
				
					break;
				case 3:
					frequency_ = (frequency_ & 0xFF00) | value;
					break;
				case 4:
					frequency_ = (frequency_ & 0x00FF) | ((value & 0x07) << 8);
					length_enabled_ = (value & 0x40) != 0;
					trigger_ = (value & 0x80) != 0;

					if (trigger_)
						trigger();

					break;
				}
			}

			void trigger()
			{
				is_enabled_ = true;

				waveform_timer_ = calculateWaveformTimer();
			}

			int calculateWaveformTimer()
			{
				return (2048 - frequency_) * 4;
			}

			uint8_t getVolume() const
			{
				return output_volume_;
			}

			bool isEnabled() const
			{
				return is_enabled_;
			}

		private:
			// NR10 FF10: -PPP NSSS Sweep period, negate, shift
			bool has_sweep_;
			uint8_t sweep_period_;
			bool negate_;
			uint8_t shift_;

			// NR11 FF11: DDLL LLLL Duty, Length load (64-L)
			uint8_t duty_;
			uint8_t length_;
			int length_counter_;

			// NR12 FF12: VVVV APPP Starting volume, Envelope add mode, period
			uint8_t volume_;
			bool envelope_add_mode_;
			uint8_t envelop_period_;

			bool dac_enabled_;
			uint8_t volume_counter_;
			int envelop_timer_;

			// NR13 FF13: FFFF FFFF Frequency LSB
			uint16_t frequency_;

			// NR14 FF14 TL-- -FFF Trigger, Length enable, Frequency MSB
			bool trigger_;
			bool length_enabled_;

			//
			bool is_enabled_;

			std::array<std::array<uint8_t, 8>, 4> waveform_;
			int waveform_idx_;
			int waveform_timer_;

			uint8_t output_volume_;

		};
	}
}

#endif // GAMEBOYCORE_SOUND_H
