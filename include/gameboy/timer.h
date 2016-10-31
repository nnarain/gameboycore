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
		\brief Opcode accurate timer
	*/
	class Timer
	{
	public:
		Timer(MMU& mmu);
		~Timer();

		void update(uint8_t cycles);

	private:
		uint8_t& controller_; // TAC
		uint8_t& counter_;    // TIMA
		uint8_t& modulo_;     // TMA
		uint8_t& divider_;    // DIV

		uint8_t m_clock_;
		uint8_t base_clock_;
		uint8_t div_clock_;

		InterruptProvider timer_interrupt_;
	};
}

#endif // GAMEBOY_TIMER_H
