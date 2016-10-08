
/**
	@author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef GAMEBOY_JOYPAD_H
#define GAMEBOY_JOYPAD_H

#include "gameboy/mmu.h"
#include "gameboy/interrupt_provider.h"

#include <functional>

namespace gb
{
	class Joypad
	{
	public:
		enum class Key
		{
			RIGHT  = 0,
			LEFT   = 1,
			UP     = 2,
			DOWN   = 3,
			A      = 4,
			B      = 5,
			SELECT = 6,
			START  = 7
		};

		Joypad(MMU& mmu) : 
			mmu_(mmu),
			reg_(mmu.get(memorymap::JOYPAD_REGISTER)),
			keys_(0xFF),
			interrupt_provider_(mmu, InterruptProvider::Interrupt::JOYPAD)
		{
			// add handlers
			mmu_.addReadHandler(memorymap::JOYPAD_REGISTER, std::bind(&Joypad::readJoypad, this));
			mmu_.addWriteHandler(memorymap::JOYPAD_REGISTER, std::bind(&Joypad::writeJoypad, this, std::placeholders::_1));
		}

		void press(Key key)
		{
			keys_ &= ~(1 << static_cast<uint8_t>(key));
			interrupt_provider_.set();
		}

		void release(Key key)
		{
			keys_ |= (1 << static_cast<uint8_t>(key));
		}

		uint8_t readJoypad()
		{
			// first 2 bits of high nybble is group selection
			uint8_t group = ((~(reg_ >> 4)) & 0x03) - 1;

			uint8_t selection = (keys_ >> (group * 4)) & 0x0F;

			return (reg_ & 0xF0) | selection;
		}

		void writeJoypad(uint8_t value)
		{
			reg_ = value | 0x0F;
		}

		~Joypad()
		{
		}

	private:
		MMU& mmu_;
		uint8_t& reg_;
		uint8_t keys_;

		InterruptProvider interrupt_provider_;
	};
}

#endif // GAMEBOY_JOYPAD_H
