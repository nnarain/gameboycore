/**
	\author Natesh Narain <nnaraindev@gmail.com>
	\data   Oct 15 2016
*/

#ifndef GAMEBOY_TIMER_H
#define GAMEBOY_TIMER_H

#include "gameboy/mmu.h"
#include "gameboy/memorymap.h"
#include "gameboy/interrupt_provider.h"

#include <cstdint>
#include <functional>

namespace gb
{
	/**
		Handle the Gameboy timer registers
	*/
	class Timer
	{
		static constexpr auto SYSTEM_CLOCK = 4200000.0;

	public:
		Timer(MMU& mmu) :
			controller_(mmu.get(memorymap::TIMER_CONTROLLER_REGISTER)),
			counter_(mmu.get(memorymap::TIMER_COUNTER_REGISTER)),
			modulo_ (mmu.get(memorymap::TIMER_MODULO_REGISTER)),
			is_enabled_(false),
			count_to_tick_(0),
			cycle_count_(0),
			timer_interrupt_(mmu, InterruptProvider::Interrupt::TIMER)
		{
			mmu.addWriteHandler(memorymap::TIMER_CONTROLLER_REGISTER, std::bind(&Timer::configure, this, std::placeholders::_1));
		}

		void clock(uint8_t cycles)
		{
			if (!is_enabled_) return;

			cycle_count_ += cycles;

			if (cycle_count_ >= count_to_tick_)
			{
				if (counter_ == 0xFF)
				{
					counter_ = modulo_;
					timer_interrupt_.set();
				}
				else
				{
					counter_++;
					cycle_count_ = 0;
				}
			}
		}

		void configure(uint8_t value)
		{
			static constexpr uint32_t SYTSEM_FREQ = 4200000u;
			static constexpr uint32_t freq_selection[] = {
				0x4096u,
				0x262144u,
				0x65536u,
				0x16384u
			};

			is_enabled_ = (value & 0x04) != 0;

			count_to_tick_ = SYTSEM_FREQ / freq_selection[value & 0x03];

			controller_ = value;
		}

		~Timer()
		{
		}

	private:
		uint8_t& controller_;
		uint8_t& counter_;
		uint8_t& modulo_;

		bool is_enabled_;
		uint32_t count_to_tick_;

		uint32_t cycle_count_;

		InterruptProvider timer_interrupt_;
	};
}

#endif // GAMEBOY_TIMER_H
