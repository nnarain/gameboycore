#include "gameboycore/mbc1.h"

namespace gb
{
	namespace detail
	{
		static constexpr unsigned int KILO_BYTE = 1024;
		static constexpr unsigned int BANK_SIZE = (16 * KILO_BYTE);

		MBC1::MBC1(uint8_t* rom, uint32_t size, uint8_t rom_size, uint8_t ram_size) :
			rom_idx_(0),
			rom_bank_lower_bits_(0),
			rom_bank_upper_bits_(0),
			ram_idx_(0),
			mode_(MemoryMode::ROM)
		{
			loadROM(rom, size, rom_size);
			loadRAM(ram_size);
		}

		void MBC1::write(uint8_t value, uint16_t addr)
		{
			switch (addr & 0xF000)
			{
			case 0x0000:
			case 0x1000:
			case 0x2000:
			case 0x3000:
			case 0x4000:
			case 0x5000:
			case 0x6000:
			case 0x7000:
				control(value, addr);
				break;
			case 0x8000:
			case 0x9000:
				ram1_[addr - 0x8000] = value;
				break;
			case 0xA000:
			case 0xB000:
				if (xram_enable_)
					switchable_ram1_[ram_idx_][addr - 0xA000] = value;
				break;
			case 0xC000:
				ram2_[addr - 0xC000] = value;
				break;
			case 0xD000:
				switchable_ram2_[0][addr - 0xD000] = value;
				break;
			case 0xE000:
			case 0xF000:
				ram3_[addr - 0xE000] = value;
				break;
			}
		}

		uint8_t MBC1::read(uint16_t addr) const
		{
			switch (addr & 0xF000)
			{
			case 0x0000:
			case 0x1000:
			case 0x2000:
			case 0x3000:
				return rom0_[addr];
			case 0x4000:
			case 0x5000:
			case 0x6000:
			case 0x7000:
				return switchable_rom_[rom_idx_][addr - 0x4000];
			case 0x8000:
			case 0x9000:
				return ram1_[addr - 0x8000];
			case 0xA000:
			case 0xB000:
				if (xram_enable_)
					return switchable_ram1_[ram_idx_][addr - 0xA000];
				else
					return 0xFF;
			case 0xC000:
				return ram2_[addr - 0xC000];
			case 0xD000:
				// TODO: CGB support
				return switchable_ram2_[0][addr - 0xD000];
			case 0xE000:
			case 0xF000:
				return ram3_[addr - 0xE000];
			}

			// Should not get here
			// TODO: assert
			return 0;
		}

		uint8_t& MBC1::get(uint16_t addr)
		{
			if (addr >= 0xE000 && addr <= 0xFFFF)
			{
				return ram3_[addr - 0xE000];
			}

			throw std::runtime_error("Cannot get reference to address below $E000");
		}

		uint8_t* MBC1::getptr(uint16_t addr)
		{
			switch (addr & 0xF000)
			{
			case 0x0000:
			case 0x1000:
			case 0x2000:
			case 0x3000:
				return &rom0_[addr];
			case 0x4000:
			case 0x5000:
			case 0x6000:
			case 0x7000:
				return &switchable_rom_[rom_idx_][addr - 0x4000];
			case 0x8000:
			case 0x9000:
				return &ram1_[addr - 0x8000];
			case 0xA000:
			case 0xB000:
				return &switchable_ram1_[ram_idx_][addr - 0xA000];
			case 0xC000:
				return &ram2_[addr - 0xC000];
			case 0xD000:
				// TODO: CGB support
				return &switchable_ram2_[0][addr - 0xD000];
			case 0xE000:
			case 0xF000:
				return &ram3_[addr - 0xE000];
			}

			return nullptr;
		}

		void MBC1::control(uint8_t value, uint16_t addr)
		{
			if (addr >= 0x0000 && addr <= 0x1FFF)
			{
				xram_enable_ = ((value & 0x0F) == 0x0A);
			}
			else if (addr >= 0x2000 && addr <= 0x3FFF)
			{
				rom_bank_lower_bits_ = value & 0x1F;

				if (mode_ == MemoryMode::ROM)
				{
					selectRomBank(rom_bank_lower_bits_, rom_bank_upper_bits_);
				}
				else
				{
					rom_bank_upper_bits_ = 0;
					selectRomBank(rom_bank_lower_bits_, rom_bank_upper_bits_);
				}
			}
			else if (addr >= 0x4000 && addr <= 0x5FFF)
			{
				if (mode_ == MemoryMode::ROM)
				{
					rom_bank_upper_bits_ = value & 0x03;
					selectRomBank(rom_bank_lower_bits_, rom_bank_upper_bits_);
				}
				else
				{
					selectRamBank(value & 0x3);
				}
			}
			else if (addr >= 0x6000 && addr <= 0x7FFF)
			{
				mode_ = static_cast<MemoryMode>(value & 0x01);

				if (mode_ == MemoryMode::RAM)
				{
					rom_bank_upper_bits_ = 0;
					selectRomBank(rom_bank_lower_bits_, rom_bank_upper_bits_);
				}
			}
		}

		void MBC1::selectRomBank(uint8_t lo, uint8_t hi)
		{
			auto bank_number = ((hi << 5) | lo);

			// potentially remap the rom bank number
			switch (bank_number)
			{
			case 0x00:
			case 0x20:
			case 0x40:
			case 0x60:
				bank_number++;
				break;
			default:
				// ...
				break;
			}

			rom_idx_ = bank_number - 1;
		}

		void MBC1::selectRamBank(uint8_t ram_bank_number)
		{
			ram_idx_ = ram_bank_number;
		}

		void MBC1::loadROM(uint8_t* rom, uint32_t size, uint8_t rom_size)
		{
			// lookup tables for number of ROM banks cartridge has
			static unsigned int rom_banks1[] = {
				2, 4, 8, 16, 32, 64, 128, 256
			};
			static unsigned int rom_banks2[] = {
				72, 80, 96
			};

			uint32_t offset = 0;

			// allocate memory for this bank
			//rom0_.resize(0x3FFF - 0x0000 + 1);
			rom0_.resize(BANK_SIZE);

			std::memcpy(&rom0_[0], rom, rom0_.size());
			offset += rom0_.size();

			auto switchable_rom_banks = 0;

			if (rom_size <= static_cast<uint8_t>(MBC::ROM::MB4))
			{
				// look up the total number of banks this cartridge has
				auto cartridge_rom_banks = rom_banks1[rom_size];
				// the number of switchable ROM banks is 2 less than the total
				// since there are always 2 available in the $0000 - $3FFF range
				switchable_rom_banks = cartridge_rom_banks - 1;
			}
			else
			{
				// the number of switchable ROM banks is 2 less than the total
				// since there are always 2 available in the $0000 - $3FFF range
				switchable_rom_banks = rom_banks2[rom_size] - 1;
			}

			switchable_rom_.resize(switchable_rom_banks);
			for (auto& bank : switchable_rom_)
			{
				bank.resize(BANK_SIZE);
				std::memcpy(&bank[0], rom + offset, bank.size());
				offset += bank.size();
			}
		}

		void MBC1::loadRAM(uint8_t ram_size)
		{
			//	XRAM_NONE = 0x00:
			//	XRAM_2KB  = 0x01: $A000 - $A7FF
			//	XRAM_8KB  = 0x02: $A000 - $BFFF
			//	XRAM_32KB = 0x03: $A000 - $BFFF x4

			// non-switchable RAM
			ram1_.resize(0x9FFF - 0x8000 + 1);
			ram2_.resize(0xCFFF - 0xC000 + 1);
			ram3_.resize(0xFFFF - 0xE000 + 1);

			// switchable RAM
			auto num_banks = (static_cast<MBC::XRAM>(ram_size) == MBC::XRAM::KB32) ? 4 : 1;

			switchable_ram1_.resize(num_banks);
			for (auto& bank : switchable_ram1_)
				bank.resize(0xBFFF - 0xA000 + 1);

			// TODO: support CGB
			switchable_ram2_.resize(1);
			switchable_ram2_.front().resize(0xDFFF - 0xD000 + 1);
		}
	}
}