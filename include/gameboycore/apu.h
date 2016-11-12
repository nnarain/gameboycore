/**
	\author Natesh Narain <nnaraindev@gmail.com>
	\date Nov 3 2016
*/


#ifndef GAMEBOYCORE_APU_H
#define GAMEBOYCORE_APU_H

#include "gameboycore/gameboycore_api.h"
#include "gameboycore/mmu.h"

#include <memory>
#include <functional>

namespace gb
{
	/**
		\brief Emulate Gameboy sound functions
	*/
	class GAMEBOYCORE_API APU
	{
	public:
		static constexpr auto CHANNEL_COUNT = 2;
		static constexpr auto SAMPLE_RATE = 44100;
		static constexpr auto CYCLES_512HZ = 8203;

	public:
		using Ptr = std::shared_ptr<APU>;

		using AudioSampleCallback = std::function<void(uint16_t, uint16_t)>;

	public:

		APU(MMU::Ptr& mmu);
		~APU();

		void update(uint8_t cycles);
		void setAudioSampleCallback(AudioSampleCallback callback);

	private:
		class Impl;
		Impl* impl_;
	};
}

#endif
