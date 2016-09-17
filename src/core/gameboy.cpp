
#include "gameboy/gameboy.h"

namespace gb
{
    Gameboy::Gameboy() :
		step_count_(1)
    {
		cpu_.setDebugMode(false);
    }

    void Gameboy::update()
    {
		for (int i = 0; i < step_count_; i++)
		{
			cpu_.step();
		}
    }

    void Gameboy::loadROM(uint8_t* rom, uint32_t size)
    {
        MMU& mmu = cpu_.getMMU();
        mmu.load(rom, size);
    }

	void Gameboy::reset()
	{
		cpu_.reset();
	}

	void Gameboy::setStepCount(unsigned int step_count)
	{
		step_count_ = step_count;
	}

	const CPU& Gameboy::getCPU() const
	{
		return cpu_;
	}

	TileRAM Gameboy::getTileRAM()
	{
		return TileRAM(cpu_.getMMU(), cpu_.getLCDController());
	}

	TileMap Gameboy::getTileMap()
	{
		const LCDController& lcd = cpu_.getLCDController();
		return TileMap(TileRAM(cpu_.getMMU(), lcd), cpu_.getMMU(), lcd);
	}

	bool Gameboy::isDone() const
	{
		return cpu_.isHalted();
	}
}
