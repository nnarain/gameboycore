#include "gameboy/mmu.h"
#include "gameboy/mbc.h"

static const unsigned int KILO_BYTE = 1024;

namespace gb
{
    MMU::MMU() :
		memory_(0xFFFF + 1)
    {
    }

    MMU::~MMU()
    {
    }

    void MMU::load(uint8_t* rom, uint32_t size)
    {
		RomParser parser;
		CartInfo info = parser.parse(rom);
    }

    uint8_t MMU::read(uint16_t addr)
    {
        return memory_[addr];
    }

    void MMU::write(uint8_t value, uint16_t addr)
    {
        // TODO: implement ROM bank switching
        memory_[addr] = value;
    }

	void MMU::loadROMBanks(CartInfo& info)
	{
		static unsigned int rom_banks1[] = {
			0, 4, 8, 16, 32, 64, 128, 256 
		};
		static unsigned int rom_banks2[] = {
			72, 80, 96
		};

		if (info.rom_size <= mbc::ROM_256KB) 
		{
			// look up the total number of banks this cartridge has
			unsigned int cartridge_rom_banks = rom_banks1[info.rom_size];
			// subtract the 2 existing ROM banks that are always available
			unsigned int switchable_banks = cartridge_rom_banks - 2;

			// allocate the banks
			rom_banks_.resize(switchable_banks);

			for (bank_t& bank : rom_banks_)
				bank.resize(16 * KILO_BYTE);
		}
		else
		{

		}
	}
}
