/**
	\author Natesh Narain <nnaraindev@gmail.com>
	\date Oct 23 2016
*/

#ifndef GAMEBOYCORE_GPU_H
#define GAMEBOYCORE_GPU_H

#include "gameboycore/mmu.h"
#include "gameboycore/memorymap.h"
#include "gameboycore/pixel.h"
#include "gameboycore/interrupt_provider.h"
#include "gameboycore/tilemap.h"

#include <memory>
#include <cstdint>
#include <functional>
#include <array>
#include <iostream>

namespace gb
{
	/**
		\brief Handle LCD state, compute scanlines and send to an external renderer
	*/
	class GPU
	{
		enum class Mode
		{
			HBLANK,
			VBLANK,
			OAM,
			LCD
		};

	public:
		using Ptr = std::shared_ptr<GPU>;

		using Scanline               = std::array<Pixel, 160>;
		using RenderScanlineCallback = std::function<void(const Scanline&, int linenum)>;

	public:
		GPU(const MMU::Ptr& mmu);
		~GPU();

		void update(uint8_t cycles, bool ime);

		void setRenderCallback(RenderScanlineCallback callback);

	private:

		void transitionState(bool ime);

		void renderScanline();

		void configure(uint8_t value);

		void checkInterrupts(uint8_t stat, bool ime);

	private:
		MMU::Ptr mmu_;

		bool is_enabled_;

		Mode mode_;
		int cycles_to_next_state_;
		int cycle_count_;
		int line_;
		int line_count_;
		RenderScanlineCallback render_scanline_;
	};
}

#endif
