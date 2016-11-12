
#include "gameboycore/gameboycore.h"

#include <memory>

namespace gb
{
	/* Private Interface */

	class GameboyCore::Impl
	{
	public:
		CPU::Ptr cpu;
		MMU::Ptr mmu;
		GPU::Ptr gpu;
		APU::Ptr apu;

		void loadROM(uint8_t* rom, uint32_t size)
		{
			mmu.reset(new MMU());
			mmu->load(rom, size);

			gpu.reset(new GPU(mmu));
			apu.reset(new APU(mmu));

			cpu.reset(new CPU(mmu, gpu, apu));
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

	CPU& GameboyCore::getCPU()
	{
		return *impl_->cpu.get();
	}

	MMU::Ptr GameboyCore::getMMU()
	{
		return impl_->mmu;
	}

	GPU::Ptr GameboyCore::getGPU()
	{
		return impl_->gpu;
	}

	APU::Ptr GameboyCore::getAPU()
	{
		return impl_->apu;
	}

	Joypad GameboyCore::getJoypad()
	{
		return Joypad(*impl_->mmu.get());
	}

	bool GameboyCore::isDone() const
	{
		return impl_->cpu->isHalted();
	}
}
