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
		\class APU
		\brief Emulate Gameboy sound functions
		\ingroup API
	*/
	class GAMEBOYCORE_API APU
	{
	public:
		static constexpr int CHANNEL_COUNT = 2;   ///< Number of audio channels the APU provides (Stereo sound: left, right)
		static constexpr int SAMPLE_RATE = 44100; ///< Audio sample rate
		static constexpr int CYCLES_512HZ = 8203;

	public:
		//! Smart pointer type
		using Ptr = std::unique_ptr<APU>;
		//! Callback used to provide audio to the host system
		using AudioSampleCallback = std::function<void(uint16_t, uint16_t)>;

	public:

		APU(MMU::Ptr& mmu);
		~APU();

		/**
			Update APU with the elasped cycles. For use by the CPU
		*/
		void update(uint8_t cycles);
		/**
			Set the host callback
		*/
		void setAudioSampleCallback(AudioSampleCallback callback);

	private:
		class Impl;
		Impl* impl_;
	};
}

#endif
