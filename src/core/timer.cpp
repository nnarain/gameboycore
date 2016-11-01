#include "gameboy/timer.h"

namespace gb
{
	Timer::Timer(MMU& mmu) :
		controller_(mmu.get(memorymap::TIMER_CONTROLLER_REGISTER)),
		counter_(mmu.get(memorymap::TIMER_COUNTER_REGISTER)),
		modulo_(mmu.get(memorymap::TIMER_MODULO_REGISTER)),
		divider_(mmu.get(memorymap::DIVIDER_REGISER)),
		m_clock_(0),
		base_clock_(0),
		div_clock_(0),
		timer_interrupt_(mmu, InterruptProvider::Interrupt::TIMER)
	{
	}

	void Timer::update(const uint8_t machine_cycles)
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
			m_clock_ += machine_cycles * 4;

//			while (m_clock_ >= 4)
//			{
//				m_clock_ -= 4;
//
//				// source clock for timers increments at 1/4 of the M clock
//				base_clock_++;
//			}

			auto threshold = freqs[controller_ & 0x03] * 4;

			while (m_clock_ >= threshold)
			{
				m_clock_ -= threshold;

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
		div_clock_ += machine_cycles;
		if (div_clock_ >= 16)
		{
			div_clock_ -= 16;
			// divider increments at 1/16 the base clock frequency
			divider_++;
			div_clock_ = 0;
		}
	}

	Timer::~Timer()
	{
	}
}