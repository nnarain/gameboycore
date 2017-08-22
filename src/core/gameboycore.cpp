
#include "gameboycore/gameboycore.h"
#include "gameboycore/cartinfo.h"

#include <memory>

namespace gb
{
	/* Private Interface */

	class GameboyCore::Impl
	{
	public:
		CPU::Ptr  cpu;
		MMU::Ptr  mmu;
		GPU::Ptr  gpu;
		APU::Ptr  apu;
		Joy::Ptr  joy;
		Link::Ptr link;

		void loadROM(uint8_t* rom, uint32_t size)
		{
			mmu.reset(new MMU(rom, size));

			gpu.reset(new GPU(mmu));
			apu.reset(new APU(mmu));
			link.reset(new Link(mmu));

			cpu.reset(new CPU(mmu, gpu, apu, link));

			joy.reset(new Joy(*mmu));

			setColorTheme(ColorTheme::GOLD);
		}

		void setColorTheme(ColorTheme theme)
		{
			switch (theme)
			{
			case gb::GameboyCore::ColorTheme::DEFAULT:
				gpu->setPaletteColor(255, 255, 255, 0);
				gpu->setPaletteColor(196, 196, 196, 1);
				gpu->setPaletteColor( 96,  96,  96, 2);
				gpu->setPaletteColor(  0,   0,   0, 3);
				break;
			case gb::GameboyCore::ColorTheme::GOLD:
				gpu->setPaletteColor(252, 232, 140, 0);
				gpu->setPaletteColor(220, 180,  92, 1);
				gpu->setPaletteColor(152, 124,  60, 2);
				gpu->setPaletteColor(76,   60,  28, 3);
				break;
			case gb::GameboyCore::ColorTheme::GREEN:
				gpu->setPaletteColor(155, 188, 15, 0);
				gpu->setPaletteColor(139, 172, 15, 1);
				gpu->setPaletteColor( 48,  98, 48, 2);
				gpu->setPaletteColor( 15,  56, 15, 3);
				break;
			default:
				break;
			}
		}
	};

	/* Public Interface */

	GameboyCore::GameboyCore() :
		impl_(new Impl)
    {
    }

	GameboyCore::~GameboyCore()
	{
		delete impl_;
	}

    void GameboyCore::update(int steps)
    {
		while(steps--)
		{
			impl_->cpu->step();
		}
    }

    void GameboyCore::loadROM(uint8_t* rom, uint32_t size)
    {
		impl_->loadROM(rom, size);
    }

	void GameboyCore::reset()
	{
		impl_->cpu->reset();
	}

	void GameboyCore::setDebugMode(bool debug)
	{
		impl_->cpu->setDebugMode(debug);
	}

	void GameboyCore::setColorTheme(ColorTheme theme)
	{
	}

	CPU::Ptr& GameboyCore::getCPU()
	{
		return impl_->cpu;
	}

	MMU::Ptr& GameboyCore::getMMU()
	{
		return impl_->mmu;
	}

	GPU::Ptr& GameboyCore::getGPU()
	{
		return impl_->gpu;
	}

	APU::Ptr& GameboyCore::getAPU()
	{
		return impl_->apu;
	}

	Joy::Ptr& GameboyCore::getJoypad()
	{
		return impl_->joy;
	}

	Link::Ptr& GameboyCore::getLink()
	{
		return impl_->link;
	}

	bool GameboyCore::isDone() const
	{
		return impl_->cpu->isHalted();
	}
}
