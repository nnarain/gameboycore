
/**
	@author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef GAMEBOY_LCD_CONTROLLER_H
#define GAMEBOY_LCD_CONTROLLER_H

#include "gameboy/mmu.h"
#include "gameboy/interrupt_provider.h"

#include <functional>
#include <cstdint>

namespace gb
{
	/**
		\brief LCD Controller Module on the Gameboy.
	*/
	class LCDController
	{
	public:
		enum class BackgroundMapData
		{
			BG_DATA_1, // $9800 - $9BFF
			BG_DATA_2  // $9C00 - $9FFF
		};

		enum class CharacterDataMode
		{
			SIGNED,   // $8800 - $97FF
			UNSIGNED  // $8000 - $8FFF
		};

		using Callback = std::function < void() >;

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

		enum LCDCBits
		{
			ENABLE                = (1 << 7),
			WINDOW_CODE_AREA      = (1 << 6),
			WINDOW_ON             = (1 << 5),
			CHARACTER_DATA        = (1 << 4),
			BG_CODE_AREA          = (1 << 3),
			OBJ_BLOCK_COMPOSITION = (1 << 2),
			OBJ_ON                = (1 << 1),
			BG_DISPLAY_ON         = (1 << 0)
		};

		enum StatBits
		{
			LYCLY = (1 << 2)
		};

		enum class State
		{
			MODE0 = 0, // H Blank
			MODE1 = 1, // V Blank
			MODE2 = 2, // OAM 
			MODE3 = 3  // Transferring to LCD driver
		};

	public:
		LCDController(MMU& mmu);
		~LCDController();

		/**
			Inform the controller of the elapsed time
		*/
		void clock(uint8_t cycles);

		void setVBlankCallback(Callback callback);

		bool isEnabled() const;
		bool isSpritesEnabled() const;
		bool isBackgroundEnabled() const;
		bool isWindowOverlayEnabled() const;

		BackgroundMapData getBackgroundMapLocation() const;
		BackgroundMapData getWindowOverlayLocation() const;
		CharacterDataMode getCharacterDataMode() const;

	private:
		void transitionState(State newState);
		void configure(uint8_t value);

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

		bool is_enabled_;

		InterruptProvider lcd_stat_provider_;
		InterruptProvider vblank_provider_;

		Callback callback_;
	};
}

#endif // GAMEBOY_LCD_CONTROLLER_H