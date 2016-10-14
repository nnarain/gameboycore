
#include "gameboy/gameboy.h"

#include <memory>

namespace gb
{
    Gameboy::Gameboy() :
		step_count_(1)
    {
    }

    void Gameboy::update()
    {
		for (auto i = 0u; i < step_count_; i++)
		{
			cpu_->step();
		}
    }

    void Gameboy::loadROM(uint8_t* rom, uint32_t size)
    {
		// TODO: load this as vector
    //    MMU& mmu = cpu_->getMMU();
    //    mmu.load(rom, size);

		mmu_ = std::make_shared<MMU>();
		mmu_->load(rom, size);

		cpu_ = std::make_unique<CPU>(mmu_);
    }

	void Gameboy::reset()
	{
		cpu_.reset();
	}

	void Gameboy::setDebugMode(bool debug)
	{
		cpu_->setDebugMode(debug);
	}

	void Gameboy::setStepCount(unsigned int step_count)
	{
		step_count_ = step_count;
	}

	CPU& Gameboy::getCPU()
	{
		return *cpu_.get();
	}

	TileRAM Gameboy::getTileRAM()
	{
		return TileRAM(cpu_->getMMU(), cpu_->getLCDController());
	}

	TileMap Gameboy::getTileMap()
	{
		const LCDController& lcd = cpu_->getLCDController();
		return TileMap(TileRAM(*mmu_.get(), lcd), *mmu_.get(), lcd);
	}

	OAM Gameboy::getOAM()
	{
		return OAM{ *mmu_.get() };
	}

	LCDController& Gameboy::getLCDController()
	{
		return cpu_->getLCDController();
	}

	Joypad Gameboy::getJoypad()
	{
		return Joypad(*mmu_.get());
	}

	bool Gameboy::isDone() const
	{
		return cpu_->isHalted();
	}
}
