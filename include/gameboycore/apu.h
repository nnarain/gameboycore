/**
	\author Natesh Narain <nnaraindev@gmail.com>
	\date Nov 3 2016
*/


#ifndef GAMEBOYCORE_APU_H
#define GAMEBOYCORE_APU_H

#include "gameboycore/mmu.h"
#include "gameboycore/channel.h"
#include "gameboycore/sound.h"
#include "gameboycore/wave.h"
#include "gameboycore/noise.h"

#include <memory>
#include <functional>

namespace gb
{
	/**
		\brief Emulate Gameboy sound functions
	*/
	class APU
	{
	public:
		static constexpr auto CHANNEL_COUNT = 2;
		static constexpr auto SAMPLE_RATE = 44100;
		static constexpr auto CYCLES_512HZ = 8203;

	public:
		using Ptr = std::shared_ptr<APU>;

		using AudioSampleCallback = std::function<void(uint16_t, uint16_t)>;

	public:

		APU(MMU::Ptr& mmu) : 
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

		~APU()
		{
		}

	private:
		void writeHandler(uint8_t value, uint16_t addr)
		{

		}

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
}

#endif
