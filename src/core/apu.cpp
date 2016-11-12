
/**
	\author Natesh Narain <nnaraindev@gmail.com>
*/

#include "gameboycore/apu.h"
#include "gameboycore/channel.h"
#include "gameboycore/sound.h"
#include "gameboycore/wave.h"
#include "gameboycore/noise.h"

namespace gb
{
	/* Private Interface */

	class APU::Impl
	{
	public:
		Impl(MMU::Ptr& mmu) :
			mmu_(mmu),
			sound1_(mmu, memorymap::NR10_REGISTER),
			sound2_(mmu, memorymap::NR20_REGISTER, false),
			wave_(mmu),
			noise_(mmu),
			master_volume_(mmu->get(memorymap::NR50_REGISTER)),
			sound_direction_(mmu->get(memorymap::NR51_REGISTER)),
			sound_enable_(mmu->get(memorymap::NR52_REGISTER)),
			timer_(0)
		{
		}

		void update(uint8_t cycles)
		{
			timer_ += cycles;

			if (has512Tick())
			{
				sound1_.update();
				sound2_.update();
				wave_.update();
				noise_.update();

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

	private:
		MMU::Ptr& mmu_;

		Sound sound1_;
		Sound sound2_;
		Wave wave_;
		Noise noise_;

		uint8_t& master_volume_;
		uint8_t& sound_direction_;
		uint8_t& sound_enable_;

		AudioSampleCallback send_audio_sample_;

		int timer_;
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