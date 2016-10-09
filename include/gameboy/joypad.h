
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

		Joypad(MMU& mmu);
		~Joypad();

		void press(Key key);

		void release(Key key);

		uint8_t readJoypad();

		void writeJoypad(uint8_t value);

	private:
		MMU& mmu_;
		uint8_t& reg_;
		uint8_t keys_;

		InterruptProvider interrupt_provider_;
	};
}

#endif // GAMEBOY_JOYPAD_H
