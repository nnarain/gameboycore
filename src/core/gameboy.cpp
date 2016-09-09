
#include "gameboy/gameboy.h"

namespace gb
{
    Gameboy::Gameboy()
    {
		cpu_.setDebugMode(true);
    }

    void Gameboy::update()
    {
		cpu_.tick();
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

	const CPU& Gameboy::getCPU() const
	{
		return cpu_;
	}

	bool Gameboy::isDone() const
	{
		return cpu_.isHalted();
	}
}
