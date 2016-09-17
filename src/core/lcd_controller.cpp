#include "gameboy/lcd_controller.h"

#include "bitutil.h"

#define SCAN_LINE_CYCLES 456
#define MAX_LINES 153

namespace gb
{
	LCDController::LCDController(MMU& mmu) :
		lcdc_(mmu.get(LCDRegister::LCDC)),
		stat_(mmu.get(LCDRegister::STAT)),
		ly_  (mmu.get(LCDRegister::LY)),
		lyc_ (mmu.get(LCDRegister::LYC)),
		state_(State::MODE2),
		line_count_(0),
		mode_count_(0),
		is_enabled_(false)
	{
	}

	void LCDController::clock(uint8_t cycles)
	{
		// check if the controller is enabled
		if (lcdc_ & LCDCBits::ENABLE)
		{
			if(!is_enabled_)
				ly_ = 0;

			is_enabled_ = true;
		}
		else
		{
			is_enabled_ = false;
		}

		if (!is_enabled_) return;

		// increment counters
		line_count_ += cycles;
		mode_count_ += cycles;

		// check scan line time
		if (line_count_ >= SCAN_LINE_CYCLES)
		{
			// increment count register. cap to 153 lines
			ly_ = (ly_ + 1) % MAX_LINES;
			line_count_ = 0;
		}

		// transition states
		switch (state_)
		{
		case State::MODE0: // H-Blank
			if (mode_count_ > 201)
			{
				if (ly_ >= 144)
				{
					transitionState(State::MODE1);
				}
				else
				{
					transitionState(State::MODE2);
				}
			}
			break;
		case State::MODE1: // V-Blank
			if (mode_count_ > 4560)
			{
				transitionState(State::MODE2);
			}
			break;
		case State::MODE2:
			if (mode_count_ > 77)
			{
				transitionState(State::MODE3);
			}
			break;
		case State::MODE3:
			if (mode_count_ > 169)
			{
				transitionState(State::MODE0);
			}
			break;
		}

		// set LYC = LY bit
		if (ly_ == lyc_)
			SET(stat_, StatBits::LYCLY);
		else
			CLR(stat_, StatBits::LYCLY);
	}

	void LCDController::transitionState(State newState)
	{
		uint8_t mode_flag = static_cast<uint8_t>(newState);

		// set mode flag in status register
		FORCE(stat_, 0x03, mode_flag);

		// set interrupts

		//
		mode_count_ = 0;
	}

	LCDController::BackgroundMapData LCDController::getBackgroundMapLocation() const
	{
		if (lcdc_ & LCDCBits::BG_CODE_AREA)
		{
			// if bit is set
			return BackgroundMapData::BG_DATA_2;
		}
		else
		{
			return BackgroundMapData::BG_DATA_1;
		}
	}

	LCDController::BackgroundMapData LCDController::getWindowOverlayLocation() const
	{
		if (lcdc_ & LCDCBits::WINDOW_CODE_AREA)
		{
			// if bit is set
			return BackgroundMapData::BG_DATA_2;
		}
		else
		{
			return BackgroundMapData::BG_DATA_1;
		}
	}

	LCDController::CharacterDataMode LCDController::getCharacterDataMode() const
	{
		if (lcdc_ & LCDCBits::CHARACTER_DATA)
		{
			return CharacterDataMode::UNSIGNED;
		}
		else
		{
			return CharacterDataMode::SIGNED;
		}
	}

	LCDController::~LCDController()
	{
	}
}