
/**
	\author Natesh Narain <nnaraindev@gmail.com>
*/

#include "gameboycore/apu.h"
#include "gameboycore/channel.h"
#include "gameboycore/square.h"
#include "gameboycore/memorymap.h"
#include "gameboycore/wave.h"
#include "gameboycore/noise.h"

#include "bitutil.h"

#include <algorithm>
#include <array>
#include <cstring>

namespace gb
{
	/* Private Interface */

	class APU::Impl
	{
		//! Cycles for 512 Hz with ~4.2 MHz clock
		static constexpr int CYCLES_512HZ = 8192;
		//! Starting address of the APU registers
		static constexpr int APU_REG_BASE = memorymap::NR10_REGISTER;

	public:
		Impl(MMU::Ptr& mmu) :
			mmu_(mmu),
			square1_(true),
			square2_(false),
			wave_(
				apu_registers[memorymap::NR30_REGISTER - APU_REG_BASE],
				apu_registers[memorymap::NR31_REGISTER - APU_REG_BASE],
				apu_registers[memorymap::NR32_REGISTER - APU_REG_BASE],
				apu_registers[memorymap::NR33_REGISTER - APU_REG_BASE],
				apu_registers[memorymap::NR34_REGISTER - APU_REG_BASE]),
			noise_(
				apu_registers[memorymap::NR41_REGISTER - APU_REG_BASE],
				apu_registers[memorymap::NR42_REGISTER - APU_REG_BASE],
				apu_registers[memorymap::NR43_REGISTER - APU_REG_BASE],
				apu_registers[memorymap::NR44_REGISTER - APU_REG_BASE]),
			frame_sequencer_counter_(CYCLES_512HZ),
			frame_sequencer_(0)
		{
			// intercept all read/write attempts here
			for (int i = memorymap::NR10_REGISTER; i <= memorymap::WAVE_PATTERN_RAM_END; ++i)
			{
				mmu->addReadHandler(i, std::bind(&Impl::read, this, std::placeholders::_1));
				mmu->addWriteHandler(i, std::bind(&Impl::write, this, std::placeholders::_1, std::placeholders::_2));
			}

			// init register memory
			std::fill(apu_registers.begin(), apu_registers.end(), 0);

			// set extra read bits
			initExtraBits();
		}

		void update(uint8_t cycles)
		{
			if (!isEnabled()) return;

			while (cycles--)
			{
				if (frame_sequencer_counter_-- <= 0)
				{
					frame_sequencer_counter_ = CYCLES_512HZ;

					clockFrameSequencer();
				}

				square1_.step();
				square2_.step();
			}

		}

		uint8_t getSound1Volume() const
		{
			return square1_.getVolume();
		}

		uint8_t getSound2Volume() const
		{
			return square2_.getVolume();
		}

		uint8_t getSound3Volume() const
		{
			return 0;
		}

		uint8_t getSound4Volume() const
		{
			return 0;
		}

		void setAudioSampleCallback(AudioSampleCallback callback)
		{
			send_audio_sample_ = callback;
		}

	private:

		void clockFrameSequencer()
		{
			switch (frame_sequencer_)
			{
			case 0:
			case 2:
				clockLength();
				square1_.clockSweep();
				break;
			case 4:
				clockLength();
				break;
			case 6:
				clockLength();
				square1_.clockSweep();
				break;
			case 7:
				clockVolume();
				// produces sound? Callback?
				break;
			}

			frame_sequencer_++;

			if (frame_sequencer_ >= 8)
			{
				frame_sequencer_ = 0;
			}
		}

		void clockLength()
		{
			square1_.clockLength();
			square2_.clockLength();
		//	wave_   .clockLength();
		//	noise_  .clockLength();
		}

		void clockVolume()
		{
			square1_.clockVolume();
			square2_.clockVolume();
		}

		bool isEnabled()
		{
			return IS_BIT_SET(apuRead(memorymap::NR52_REGISTER), 7) != 0;
		}

		uint8_t read(uint16_t addr)
		{
			uint8_t value = 0;

			auto extras = extra_bits_[addr - APU_REG_BASE];

			if (addr == memorymap::NR52_REGISTER)
			{
				value &= 0xF0;

				value |= square1_.isEnabled() << 0;
				value |= square2_.isEnabled() << 1;
			//	value |= wave_   .isEnabled() << 2;
			//	value |= noise_  .isEnabled() << 3;
			}
			else
			{
				if (addr >= memorymap::NR10_REGISTER && addr <= memorymap::NR14_REGISTER)
				{
					value = square1_.read(addr - memorymap::NR10_REGISTER);
				}
				else if (addr >= memorymap::NR20_REGISTER && addr <= memorymap::NR24_REGISTER)
				{
					value = square2_.read(addr - memorymap::NR20_REGISTER);
				}
			}

			return value;
		}

		void write(uint8_t value, uint16_t addr)
		{
			if (addr == memorymap::NR52_REGISTER)
			{
				// check if APU is being disabled
				if (IS_CLR(value, 0x80))
				{
					clearRegisters();
					frame_sequencer_ = 0;
				}

				// check is being enabled
				if (!isEnabled() && IS_SET(value, 0x80))
				{
					frame_sequencer_counter_ = CYCLES_512HZ;
				}

				apuWrite(value, addr);
			}
			else
			{
				if (isEnabled())
				{
					if (addr >= memorymap::NR10_REGISTER && addr <= memorymap::NR14_REGISTER)
					{
						square1_.write(value, addr - memorymap::NR10_REGISTER);
					}
					else if (addr >= memorymap::NR20_REGISTER && addr <= memorymap::NR24_REGISTER)
					{
						square2_.write(value, addr - memorymap::NR20_REGISTER);
					}
				}
			}
		}

		uint8_t apuRead(uint16_t addr)
		{
			return apu_registers[addr - APU_REG_BASE];
		}

		void apuWrite(uint8_t value, uint16_t addr)
		{
			apu_registers[addr - APU_REG_BASE] = value;
		}

		void clearRegisters()
		{
			for (auto i = APU_REG_BASE; i < memorymap::WAVE_PATTERN_RAM_START; ++i)
			{
				apuWrite(0, i);
			}
		}

		void initExtraBits()
		{
			// NR10 - NR14
			extra_bits_[0x00] = 0x80;
			extra_bits_[0x01] = 0x3F;
			extra_bits_[0x02] = 0x00;
			extra_bits_[0x03] = 0xFF;
			extra_bits_[0x04] = 0xBF;

			// NR20 - NR24
			extra_bits_[0x05] = 0xFF;
			extra_bits_[0x06] = 0x3F;
			extra_bits_[0x07] = 0x00;
			extra_bits_[0x08] = 0xFF;
			extra_bits_[0x09] = 0xBF;

			// NR30 - NR34
			extra_bits_[0x0A] = 0x7F;
			extra_bits_[0x0B] = 0xFF;
			extra_bits_[0x0C] = 0x9F;
			extra_bits_[0x0D] = 0xFF;
			extra_bits_[0x0E] = 0xBF;

			// NR40 - NR44
			extra_bits_[0x0F] = 0xFF;
			extra_bits_[0x10] = 0xFF;
			extra_bits_[0x11] = 0x00;
			extra_bits_[0x12] = 0x00;
			extra_bits_[0x13] = 0xBF;

			// NR50 - NR52
			extra_bits_[0x14] = 0x00;
			extra_bits_[0x15] = 0x00;
			extra_bits_[0x16] = 0x70;

			//
			extra_bits_[0x17] = 0xFF;
			extra_bits_[0x18] = 0xFF;
			extra_bits_[0x19] = 0xFF;
			extra_bits_[0x1A] = 0xFF;
			extra_bits_[0x1B] = 0xFF;
			extra_bits_[0x1C] = 0xFF;
			extra_bits_[0x1D] = 0xFF;
			extra_bits_[0x1E] = 0xFF;
			extra_bits_[0x1F] = 0xFF;

			// wave ram
			extra_bits_[0x20] = 0x00;
			extra_bits_[0x21] = 0x00;
			extra_bits_[0x22] = 0x00;
			extra_bits_[0x23] = 0x00;
			extra_bits_[0x24] = 0x00;
			extra_bits_[0x25] = 0x00;
			extra_bits_[0x26] = 0x00;
			extra_bits_[0x27] = 0x00;
			extra_bits_[0x28] = 0x00;
			extra_bits_[0x29] = 0x00;
			extra_bits_[0x2A] = 0x00;
			extra_bits_[0x2B] = 0x00;
			extra_bits_[0x2C] = 0x00;
			extra_bits_[0x2D] = 0x00;
			extra_bits_[0x2E] = 0x00;
			extra_bits_[0x2F] = 0x00;
		}

	private:
		MMU::Ptr& mmu_;

		detail::Square square1_;
		detail::Square square2_;
		detail::Wave   wave_;
		detail::Noise  noise_;

		//! callback to host when an audio sample is computed
		AudioSampleCallback send_audio_sample_;

		//! APU cycle counter
		int frame_sequencer_counter_;

		//! APU internal timer
		int frame_sequencer_;

		//! APU registers
		std::array<uint8_t, 0x30> apu_registers;

		//! bits that are ORed into the value when read
		std::array<uint8_t, 0x30> extra_bits_;
	};

	/* Public Interface */

	APU::APU(MMU::Ptr& mmu) :
		impl_(new Impl(mmu))
	{
	}

	void APU::update(uint8_t cycles)
	{
		impl_->update(cycles);
	}
	
	uint8_t APU::getSound1Volume()
	{
		return impl_->getSound1Volume();
	}

	uint8_t APU::getSound2Volume()
	{
		return impl_->getSound2Volume();
	}

	uint8_t APU::getSound3Volume()
	{
		return impl_->getSound3Volume();
	}

	uint8_t APU::getSound4Volume()
	{
		return impl_->getSound4Volume();
	}

	void APU::setAudioSampleCallback(AudioSampleCallback callback)
	{
		impl_->setAudioSampleCallback(callback);
	}

	APU::~APU()
	{
		delete impl_;
	}
}