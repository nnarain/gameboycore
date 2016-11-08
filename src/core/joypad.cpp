/**
	\author Natesh Narain <nnaraindev@gmail.com>
	\date Oct 8 2016
*/

#include "gameboy/joypad.h"

namespace gb
{
	Joypad::Joypad(MMU& mmu) :
		mmu_(mmu),
		reg_(mmu.get(memorymap::JOYPAD_REGISTER)),
		keys_(0xFF),
		interrupt_provider_(mmu, InterruptProvider::Interrupt::JOYPAD)
	{
		// add handlers
		mmu_.addReadHandler(memorymap::JOYPAD_REGISTER, std::bind(&Joypad::readJoypad, this));
	}

	Joypad::~Joypad()
	{
	}

	void Joypad::press(Key key)
	{
		keys_ &= ~(1 << static_cast<uint8_t>(key));
		interrupt_provider_.set();
	}

	void Joypad::release(Key key)
	{
		keys_ |= (1 << static_cast<uint8_t>(key));
	}

	uint8_t Joypad::readJoypad()
	{
		uint8_t hi = (reg_ & 0xF0);

		if ((hi & 0x30) == 0x10 || (hi & 0x30) == 0x20)
		{
			// first 2 bits of high nybble is group selection
			uint8_t group = ((~(reg_ >> 4)) & 0x03) - 1;

			uint8_t selection = (keys_ >> (group * 4)) & 0x0F;

			return (reg_ & 0xF0) | selection;
		}
		else
		{
			return reg_ | 0x0F;
		}
	}

	void Joypad::writeJoypad(uint8_t value)
	{
		reg_ = value | 0x0F;
	}
}