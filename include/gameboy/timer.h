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
			divider_(mmu.get(memorymap::DIVIDER_REGISER)),
			t_clock_(0),
			m_clock_(0),
			base_clock_(0),
			div_clock_(0),
			is_enabled_(false),
			count_to_tick_(0),
			cycle_count_(0),
			timer_interrupt_(mmu, InterruptProvider::Interrupt::TIMER)
		{
		//	mmu.addWriteHandler(memorymap::TIMER_CONTROLLER_REGISTER, std::bind(&Timer::configure, this, std::placeholders::_1));
		}

		void clock(uint8_t cycles)
		{
			// check for timer register steps
			if (controller_ & 0x04)
			{
				static constexpr uint8_t freqs[] = {
					64, // 4   KHz
					1,  // 262 KHz (base)
					4,  // 65  KHz
					16  // 16  KHz
				};

				// M clock increments at 1/4 the T clock rate
				m_clock_ += cycles;

				while (m_clock_ >= 4)
				{
					m_clock_ -= 4;

					// source clock for timers increments at 1/4 of the M clock
					base_clock_++;
				}

				auto threshold = freqs[controller_ & 0x03];

				while (base_clock_ >= threshold)
				{
					base_clock_ -= threshold;

					if (counter_ == 0xFF)
					{
						counter_ = modulo_;
						timer_interrupt_.set();
					}
					else
					{
						counter_++;
					}
				}
			}

			// Divider Register
			div_clock_ += cycles;
			if (div_clock_ >= 16)
			{
				div_clock_ -= 16;
				// divider increments at 1/16 the base clock frequency
				divider_++;
				div_clock_ = 0;
			}
		}

		void configure(uint8_t value)
		{
			// TODO: remove this function

			static constexpr uint32_t SYTSEM_FREQ = 4200000u;
			static constexpr uint32_t freq_selection[] = {
				4096u,
				262144u,
				65536u,
				16384u
			};

		//	is_enabled_ = (value & 0x04) != 0;

			count_to_tick_ = SYTSEM_FREQ / freq_selection[value & 0x03];

			controller_ = value;
		}

		~Timer()
		{
		}

	private:
		uint8_t& controller_; // TAC
		uint8_t& counter_;    // TIMA
		uint8_t& modulo_;     // TMA
		uint8_t& divider_;    // DIV

		uint8_t t_clock_;
		uint8_t m_clock_;
		uint8_t base_clock_;
		uint8_t div_clock_;

		bool is_enabled_;
		uint32_t count_to_tick_;

		uint32_t cycle_count_;

		InterruptProvider timer_interrupt_;
	};
}

#endif // GAMEBOY_TIMER_H
