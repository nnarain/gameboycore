
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
		mmu_.reset(new MMU());
		mmu_->load(rom, size);

		gpu_.reset(new GPU(mmu_));

		cpu_.reset(new CPU(mmu_, gpu_));
    }

	void Gameboy::reset()
	{
		cpu_->reset();
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

	MMU::Ptr Gameboy::getMMU()
	{
		return mmu_;
	}

	GPU::Ptr Gameboy::getGPU()
	{
		return gpu_;
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
