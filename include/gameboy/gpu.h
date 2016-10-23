/**
	\author Natesh Narain <nnaraindev@gmail.com>
	\date Oct 23 2016
*/

#ifndef GAMEBOY_GPU_H
#define GAMEBOY_GPU_H

#include "gameboy/mmu.h"
#include "gameboy/memorymap.h"
#include "gameboy/pixel.h"
#include "gameboy/interrupt_provider.h"

#include <memory>
#include <cstdint>
#include <functional>
#include <array>

namespace gb
{
	/**
		\brief Handle LCD state, compute scanlines and send to an external renderer
	*/
	class GPU
	{
		static constexpr auto HBLANK_CYCLES       = 207;
		static constexpr auto VBLANK_CYCLES       = 4560;
		static constexpr auto OAM_ACCESS_CYCLES   = 83;
		static constexpr auto LCD_TRANSFER_CYCLES = 175;

		static constexpr auto VBLANK_LINE = 144;
		static constexpr auto LINE_MAX    = 153;

		enum class Mode
		{
			HBLANK,
			VBLANK,
			OAM,
			LCD
		};

		enum LCDCBits
		{
			ENABLE = (1 << 7),
			WINDOW_CODE_AREA = (1 << 6),
			WINDOW_ON = (1 << 5),
			CHARACTER_DATA = (1 << 4),
			BG_CODE_AREA = (1 << 3),
			OBJ_BLOCK_COMPOSITION = (1 << 2),
			OBJ_ON = (1 << 1),
			BG_DISPLAY_ON = (1 << 0)
		};

		enum StatBits
		{
			LYCLY = (1 << 2)
		};

	public:
		using Ptr = std::shared_ptr<GPU>;

		using Scanline               = std::array<Pixel, 120>;
		using RenderScanlineCallback = std::function<void(const Scanline&, int linenum)>;

	public:
		GPU(const MMU::Ptr& mmu) : 
			mmu_(mmu),
			mode_(Mode::OAM),
			is_enabled_(false),
			cycles_to_next_state_(OAM_ACCESS_CYCLES),
			cycle_count_(0),
			line_(0)
		{
		//	mmu_->addWriteHandler(memorymap::LCDC_REGISTER, std::bind(&GPU::configure, this, std::placeholders::_1));
		}

		void update(uint8_t cycles, bool ime)
		{
			// increment cycle count
			cycle_count_ += cycles;

			// check if cycle time for the current state has elapsed
			if (cycle_count_ >= cycles_to_next_state_)
			{
				// reset the cycle time
				cycle_count_ -= cycles_to_next_state_;

				// transition to next LCD driver mode.
				transitionState(ime);
			}
		}

		void setRenderCallback(RenderScanlineCallback callback)
		{
			render_scanline_ = callback;
		}

		~GPU()
		{
		}

	private:

		void transitionState(bool ime)
		{
			// switch on the current mode and determine the next mode
			switch (mode_)
			{
			case Mode::HBLANK:
				if (line_ > VBLANK_LINE)
				{
					mode_ = Mode::VBLANK;
					cycles_to_next_state_ = VBLANK_CYCLES;
				}
				else
				{
					mode_ = Mode::OAM;
					cycles_to_next_state_ = OAM_ACCESS_CYCLES;
				}
				break;
			case Mode::VBLANK:
				// vblank interrupt
				mode_ = Mode::OAM;
				cycles_to_next_state_ = OAM_ACCESS_CYCLES;
				break;
			case Mode::OAM:
				// set new cycle wait time
				mode_ = Mode::LCD;
				cycles_to_next_state_ = LCD_TRANSFER_CYCLES;
				break;
			case Mode::LCD:
				// set new cycle wait time
				mode_ = Mode::HBLANK;
				cycles_to_next_state_ = HBLANK_CYCLES;

				// compute the current scan line
				renderScanline();
				break;
			}

			// get lcd stat register
			auto stat = mmu_->read(memorymap::LCD_STAT_REGISTER);

			// update mode in register
			stat = (stat & ~(0x03)) | (static_cast<uint8_t>(mode_) & 0x03);

			// check scan line and LYC register match
			auto lyc = mmu_->read(memorymap::LYC_REGISTER);

			if ((uint8_t)line_ == lyc)
			{
				stat |= StatBits::LYCLY;
			}
			else
			{
				stat &= (~StatBits::LYCLY);
			}

			checkInterrupts(stat, ime);

			// update stat register
			mmu_->write(stat, memorymap::LCD_STAT_REGISTER);
		}

		void renderScanline()
		{
			// default color palette
			static const Pixel palette[] = {
				Pixel(255),
				Pixel(192),
				Pixel(96),
				Pixel(0)
			};

			Scanline scanline;

			// ...

			// send scan line to the renderer
			if(render_scanline_)
				render_scanline_(scanline, line_);

			line_++;
			mmu_->write((uint8_t)line_, memorymap::LY_REGISTER);
		}

		void configure(uint8_t value)
		{
			bool enable = (value & LCDCBits::ENABLE) != 0;

			if (enable && !is_enabled_)
				line_ = 0;

			is_enabled_ = enable;

			mmu_->write(value, memorymap::LCDC_REGISTER);
		}

		void checkInterrupts(uint8_t stat, bool ime)
		{
			InterruptProvider vblank_provider{ *mmu_.get(), InterruptProvider::Interrupt::VBLANK };
			InterruptProvider stat_provider  { *mmu_.get(), InterruptProvider::Interrupt::LCDSTAT };

			// check the lyc=ly flag
			if (stat & StatBits::LYCLY)
			{
				if (ime)
					stat_provider.set();
			}

			// check mode selection interrupts
			uint8_t mask = (1 << (3 + static_cast<uint8_t>(mode_)));

			if (stat & mask)
			{
				if (ime)
					vblank_provider.set();
			}
		}

	private:
		MMU::Ptr mmu_;

		bool is_enabled_;

		Mode mode_;
		int cycles_to_next_state_;
		int cycle_count_;
		int line_;
		RenderScanlineCallback render_scanline_;
	};
}

#endif
