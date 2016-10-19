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
			counter_(mmu.get(memorymap::TIMER_COUNTER_REGISTER)),
			modulo_ (mmu.get(memorymap::TIMER_MODULO_REGISTER)),
			is_enabled_(false),
			clock_period_(0),
			cycle_count_(0),
			timer_interrupt_(mmu, InterruptProvider::Interrupt::TIMER)
		{
			mmu.addWriteHandler(memorymap::TIMER_CONTROLLER_REGISTER, std::bind(&Timer::configure, this, std::placeholders::_1));
		}

		void clock(uint8_t cycles)
		{
			if (!is_enabled_) return;

			cycle_count_ += cycles;

			// use elapsed clock cycles to determine time past
			double elapsed = ((double)cycle_count_) * (1.f / SYSTEM_CLOCK);

			// if time elapsed in greater than the clock period, increment the counter
			if (elapsed >= clock_period_)
			{
				// if the counter is going to overflow, set timer overflow interrupt and load modulo register
				if (counter_ == 0xFF)
				{
					counter_ = modulo_;
					timer_interrupt_.set();
				}

				counter_++;
				cycle_count_ = 0;
			}
		}

		void configure(uint8_t value)
		{
			constexpr double clock_modes[] = {
				1.f / 4096.f,
				1.f / 262144.f,
				1.f / 65536.f,
				1.f / 16384.f
			};

			is_enabled_ = (value & 0x04) != 0;

			clock_period_ = clock_modes[value & 0x03];
		}

		~Timer()
		{
		}

	private:
		uint8_t& counter_;
		uint8_t& modulo_;

		bool is_enabled_;
		double clock_period_;

		uint32_t cycle_count_;

		InterruptProvider timer_interrupt_;
	};
}

#endif // GAMEBOY_TIMER_H
