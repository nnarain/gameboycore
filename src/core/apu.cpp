
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
			square1_(
				apu_registers[memorymap::NR11_REGISTER - APU_REG_BASE],
				apu_registers[memorymap::NR12_REGISTER - APU_REG_BASE], 
				apu_registers[memorymap::NR13_REGISTER - APU_REG_BASE],
				apu_registers[memorymap::NR14_REGISTER - APU_REG_BASE]),
			square2_(
				apu_registers[memorymap::NR21_REGISTER - APU_REG_BASE],
				apu_registers[memorymap::NR22_REGISTER - APU_REG_BASE],
				apu_registers[memorymap::NR23_REGISTER - APU_REG_BASE],
				apu_registers[memorymap::NR24_REGISTER - APU_REG_BASE], false),
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
			cycle_count_(0),
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

			cycle_count_ += cycles;

			if (has512Hz())
			{
				// decrement cycle counter
				cycle_count_ -= CYCLES_512HZ;

				// clock the frame sequencer
				clockFrameSequencer();
			}
		}

		void setAudioSampleCallback(AudioSampleCallback callback)
		{
			send_audio_sample_ = callback;
		}

	private:

		void clockFrameSequencer()
		{
			switch (frame_sequencer_++)
			{
			case 0:
			case 2:
				clockLength();
				// TODO: Sweep
				break;
			case 4:
				clockLength();
				break;
			case 6:
				clockLength();
				// TODO: Sweep
				break;
			case 7:
				// TODO: volume

				frame_sequencer_ = 0;
				break;
			}
		}

		void clockLength()
		{
			square1_.clockLength();
			square2_.clockLength();
			wave_   .clockLength();
			noise_  .clockLength();
		}

		bool has512Hz()
		{
			return cycle_count_ >= CYCLES_512HZ;
		}

		bool isEnabled()
		{
			return IS_BIT_SET(apuRead(memorymap::NR52_REGISTER), 7) != 0;
		}

		uint8_t read(uint16_t addr)
		{
			auto value = apuRead(addr) | extra_bits_[addr - APU_REG_BASE];

			if (addr == memorymap::NR52_REGISTER)
			{
				value &= 0xF0;

				value |= square1_.isEnabled() << 0;
				value |= square2_.isEnabled() << 1;
				value |= wave_   .isEnabled() << 2;
				value |= noise_  .isEnabled() << 3;
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

				apuWrite(value, addr);
			}
			else
			{
				if (isEnabled())
				{
					switch (addr)
					{
					/* Sound 1 */
					case memorymap::NR11_REGISTER:
						// set the sound length in the channel
						square1_.setLength(64 - (value & detail::Square::LENGTH_MASK));
						break;
					case memorymap::NR12_REGISTER:
						square1_.setDacPower(value >> 4);
						break;
					case memorymap::NR14_REGISTER:
						if(IS_SET(value, 0x80))
							square1_.trigger();
						break;

					/* Sound 2 */
					case memorymap::NR21_REGISTER:
						square2_.setLength(64 - (value & detail::Square::LENGTH_MASK));
						break;
					case memorymap::NR22_REGISTER:
						square2_.setDacPower(value >> 4);
						break;
					case memorymap::NR24_REGISTER:
						if (IS_SET(value, 0x80))
							square2_.trigger();
						break;

					/* Sound 3 */
					case memorymap::NR30_REGISTER:
						wave_.setDacPower(value & 0x80);
						break;
					case memorymap::NR31_REGISTER:
						wave_.setLength(256 - (value & detail::Wave::LENGTH_MASK));
						break;
					case memorymap::NR34_REGISTER:
						if (IS_SET(value, 0x80))
							wave_.trigger();
						break;

					/* Sound 4 */
					case memorymap::NR41_REGISTER:
						noise_.setLength(64 - (value & detail::Noise::LENGTH_MASK));
						break;
					case memorymap::NR42_REGISTER:
						noise_.setDacPower(value >> 4);
						break;
					case memorymap::NR44_REGISTER:
						if (IS_SET(value, 0x80))
							noise_.trigger();
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

		detail::Square square1_;
		detail::Square square2_;
		detail::Wave   wave_;
		detail::Noise  noise_;

		//! callback to host when an audio sample is computed
		AudioSampleCallback send_audio_sample_;

		//! APU cycle counter
		int cycle_count_;

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
	
	void APU::setAudioSampleCallback(AudioSampleCallback callback)
	{
		impl_->setAudioSampleCallback(callback);
	}

	APU::~APU()
	{
		delete impl_;
	}
}