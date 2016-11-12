/**
	\author Natesh Narain <nnaraindev@gmail.com>
	\date Oct 23 2016
*/

#ifndef GAMEBOYCORE_GPU_H
#define GAMEBOYCORE_GPU_H

#include "gameboycore_api.h"
#include "gameboycore/mmu.h"
#include "gameboycore/pixel.h"

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
	class GAMEBOYCORE_API GPU
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
		class Impl;
		Impl* impl_;
	};
}

#endif
