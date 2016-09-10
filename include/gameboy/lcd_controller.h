
/**
	@author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef GAMEBOY_LCD_CONTROLLER_H
#define GAMEBOY_LCD_CONTROLLER_H

#include "gameboy/mmu.h"

#include <cstdint>

namespace gb
{
	/**
		\brief LCD Controller Module on the Gameboy.
	*/
	class LCDController
	{
	private:
		enum LCDRegister
		{
			LCDC = 0xFF40,
			STAT = 0xFF41,
			SCY  = 0xFF42,
			SCX  = 0xFF43,
			LY   = 0xFF44,
			LYC  = 0xFF45
		};

		enum class State
		{
			MODE0 = 0, MODE1 = 1, MODE2 = 2, MODE3 = 3
		};

	public:
		LCDController(MMU& mmu);
		~LCDController();

		/**
			Inform the controller of the elapsed time
		*/
		void clock(uint8_t cycles);

	private:
		void transitionState(State newState);

	private:
		/* References to Gameboy LCD registers */

		uint8_t& lcdc_;
		uint8_t& stat_;
		uint8_t& ly_;
		uint8_t& lyc_;

		// number of cycles elapsed for a current scan line
		uint32_t line_count_;

		// number of cyces elapsed for the current LCD controller mode
		uint32_t mode_count_;

		// current LCD controller state
		State state_;
	};
}

#endif // GAMEBOY_LCD_CONTROLLER_H