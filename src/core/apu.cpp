
/**
	\author Natesh Narain <nnaraindev@gmail.com>
*/

#include "gameboycore/apu.h"
#include "gameboycore/channel.h"
#include "gameboycore/sound.h"
#include "gameboycore/wave.h"
#include "gameboycore/noise.h"

#include "bitutil.h"

#include <array>
#include <cstring>

namespace gb
{
	/* Private Interface */

	class APU::Impl
	{
		static constexpr int CYCLES_512HZ = 8203;
		static constexpr int APU_REG_BASE = memorymap::NR10_REGISTER;

	public:
		Impl(MMU::Ptr& mmu) :
			mmu_(mmu),
			sound1_(apu_registers[memorymap::NR11_REGISTER - APU_REG_BASE]),
			sound2_(apu_registers[memorymap::NR21_REGISTER - APU_REG_BASE], false),
			wave_(mmu),
			noise_(mmu),
			timer_(0)
		{
			// the APU does weird things to memory so intercept all read/write attempts here
			for (int i = memorymap::NR10_REGISTER; i <= memorymap::WAVE_PATTERN_RAM_END; ++i)
			{
				mmu->addReadHandler(i, std::bind(&Impl::read, this, std::placeholders::_1));
				mmu->addWriteHandler(i, std::bind(&Impl::write, this, std::placeholders::_1, std::placeholders::_2));
			}

			// init register memory
			std::memset(&apu_registers[0], 0, apu_registers.size());

			// set extra read bits
			initExtraBits();
		}

		void update(uint8_t cycles)
		{
			timer_ += cycles;

			if (has512Tick())
			{
				sound1_.update();
				sound2_.update();
				wave_  .update();
				noise_ .update();

				timer_ -= CYCLES_512HZ;
			}
		}

		void setAudioSampleCallback(AudioSampleCallback callback)
		{
			send_audio_sample_ = callback;
		}

	private:
		bool has512Tick()
		{
			return timer_ >= CYCLES_512HZ;
		}

		uint8_t read(uint16_t addr)
		{
			auto value = apuRead(addr) | extra_bits_[addr - APU_REG_BASE];

			if (addr == memorymap::NR52_REGISTER)
			{
				value &= 0xF0;

				value |= sound1_.isEnabled() << 0;
				value |= sound2_.isEnabled() << 1;
				value |= wave_.isEnabled()   << 2;
				value |= noise_.isEnabled()  << 3;
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
				}

				apuWrite(value, addr);
			}
			else
			{
				if (apuRead(memorymap::NR52_REGISTER) & 0x80)
				{
					// check if initializing a channel
					switch (addr)
					{
					case memorymap::NR14_REGISTER:
						if(IS_SET(value, 0x80))
							sound1_.restart();
						break;
					case memorymap::NR24_REGISTER:
						if (IS_SET(value, 0x80))
							sound2_.restart();
						break;
					case memorymap::NR34_REGISTER:
						if (IS_SET(value, 0x80))
							wave_.restart();
						break;
					case memorymap::NR44_REGISTER:
						if (IS_SET(value, 0x80))
							noise_.restart();
						break;
					}

					apuWrite(value, addr);
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

		detail::Sound sound1_;
		detail::Sound sound2_;
		detail::Wave wave_;
		detail::Noise noise_;

		//! callback to host when an audio sample is computed
		AudioSampleCallback send_audio_sample_;

		//! APU internal timer
		int timer_;

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
	
	void APU::setAudioSampleCallback(AudioSampleCallback callback)
	{
		impl_->setAudioSampleCallback(callback);
	}

	APU::~APU()
	{
		delete impl_;
	}
}