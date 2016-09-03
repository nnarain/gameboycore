#include "gameboy/mmu.h"
#include "gameboy/mbc.h"

#include <cstring>

static const unsigned int KILO_BYTE = 1024;
static const unsigned int BANK_SIZE = (16 * KILO_BYTE);

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

		loadROMBanks(info.rom_size, rom);
    }

    uint8_t MMU::read(uint16_t addr) const
    {
        return memory_[addr];
    }

    void MMU::write(uint8_t value, uint16_t addr)
    {
        // TODO: implement ROM bank switching
        memory_[addr] = value;
    }

	void MMU::write(uint16_t value, uint16_t addr)
	{
		uint8_t hi = (value & 0xFF00) >> 8;
		uint8_t lo = (value & 0x00FF);

		memory_[addr]     = lo;
		memory_[addr + 1] = hi;
	}

	void MMU::loadROMBanks(uint8_t rom_size, uint8_t * rom)
	{
		static unsigned int rom_banks1[] = {
			2, 4, 8, 16, 32, 64, 128, 256 
		};
		static unsigned int rom_banks2[] = {
			72, 80, 96
		};

		// copy first 2 banks to permanent ROM banks
		std::memcpy(&memory_[0], rom, 2 * BANK_SIZE);

		// load additional, switchable banks
		if (rom_size <= mbc::ROM_256KB)
		{
			// look up the total number of banks this cartridge has
			unsigned int cartridge_rom_banks = rom_banks1[rom_size];
			// the number of switchable ROM banks is 2 less than the total
			// since there are always 2 available in the $0000 - $3FFF range
			unsigned int switchable_rom_banks = cartridge_rom_banks - 2;

			if (cartridge_rom_banks != 0) 
			{
				rom_banks_.clear();
				rom_banks_.resize(switchable_rom_banks);
				copyROMToBanks(switchable_rom_banks, rom);
			}
		}
		else
		{
			// the number of switchable ROM banks is 2 less than the total
			// since there are always 2 available in the $0000 - $3FFF range
			unsigned int switchable_rom_banks = rom_banks2[rom_size] - 2;

			rom_banks_.clear();
			rom_banks_.resize(switchable_rom_banks);
			copyROMToBanks(switchable_rom_banks, rom);
		}
	}

	void MMU::copyROMToBanks(unsigned int num_banks, uint8_t* rom)
	{
		// copy ROM image into banks
		for (unsigned int i = 0; i < num_banks; ++i)
		{
			ROMBank& bank = rom_banks_[i];
			bank.resize(16 * KILO_BYTE);

			// offset into ROM to the start of the ROM bank
			// (i+2) -> skip first 2 banks (already copied)
			auto offset = (i + 2) * BANK_SIZE;
			auto current_bank = rom + offset;

			std::memcpy(&bank[0], current_bank, BANK_SIZE);
		}
	}

	unsigned int MMU::numBanks() const
	{
		return rom_banks_.size();
	}
}
