
/**
	\author Natesh Narain <nnaraindev@gmail.com>
	\date Oct 11 2016
*/

#ifndef GAMEBOY_MBC1_H
#define GAMEBOY_MBC1_H

#include "gameboy/mbc.h"

#include <vector>

namespace gb
{
	class MBC1 : public MBC
	{
	private:
		static constexpr unsigned int KILO_BYTE = 1024;
		static constexpr unsigned int BANK_SIZE = (16 * KILO_BYTE);

		/*!
			RAM or ROM bank switching mode
		*/
		enum class MemoryMode
		{
			ROM = 0, RAM = 1 ///< determines how address range $4000 - $5000 is used
		};

	public:
		MBC1(uint8_t* rom, uint32_t size, uint8_t rom_size, uint8_t ram_size) :
			rom_idx_(0),
			ram_idx_(0),
			rom_idx_upper_bits_(0)
		{
			loadROM(rom, size, rom_size);
			loadRAM(ram_size);
		}

		virtual void write(uint8_t value, uint16_t addr)
		{
			if (addr >= 0x0000 && addr <= 0x7FFF)
			{
				// write to ROM
				// handle write to MBC control registers
				control(value, addr);
			}
			else if (addr >= 0x8000 && addr <= 0x9FFF)
			{
				ram1_[addr - 0x8000] = value;
			}
			else if (addr >= 0xA000 && addr <= 0xBFFF)
			{
				switchable_ram1_[ram_idx_][addr - 0xA000] = value;
			}
			else if (addr >= 0xC000 && addr <= 0xCFFF)
			{
				ram2_[addr - 0xC000] = value;
			}
			else if (addr >= 0xD000 && addr <= 0xDFFF)
			{
				// TODO: CGB support
				switchable_ram2_[0][addr - 0xD000] = value;
			}
			else
			{
				ram3_[addr - 0xE000] = value;
			}
		}

		virtual uint8_t read(uint16_t addr) const
		{
			if (addr >= 0x0000 && addr <= 0x3FFF)
			{
				return rom0_[addr];
			}
			else if (addr >= 0x4000 && addr <= 0x7FFF)
			{
				return switchable_rom_[rom_idx_][addr - 0x4000];
			}
			else if (addr >= 0x8000 && addr <= 0x9FFF)
			{
				return ram1_[addr - 0x8000];
			}
			else if (addr >= 0xA000 && addr <= 0xBFFF)
			{
				return switchable_ram1_[ram_idx_][addr - 0xA000];
			}
			else if (addr >= 0xC000 && addr <= 0xCFFF)
			{
				return ram2_[addr - 0xC000];
			}
			else if (addr >= 0xD000 && addr <= 0xDFFF)
			{
				// TODO: CGB support
				return switchable_ram2_[0][addr - 0xD000];
			}
			else
			{
				return ram3_[addr - 0xE000];
			}

			// Should not get here
			// TODO: assert
			return 0;
		}

		virtual uint8_t& get(uint16_t addr)
		{
			if (addr >= 0xE000 && addr <= 0xFFFF)
			{
				return ram3_[addr - 0xE000];
			}

			throw std::runtime_error("Cannot get reference to address below $E000");
		}

		virtual uint8_t* getptr(uint16_t addr)
		{
			if (addr >= 0x0000 && addr <= 0x3FFF)
			{
				return &rom0_[addr];
			}
			else if (addr >= 0x4000 && addr <= 0x7FFF)
			{
				return &switchable_rom_[rom_idx_][addr - 0x4000];
			}
			else if (addr >= 0x8000 && addr <= 0x9FFF)
			{
				return &ram1_[addr - 0x8000];
			}
			else if (addr >= 0xA000 && addr <= 0xBFFF)
			{
				return &switchable_ram1_[ram_idx_][addr - 0xA000];
			}
			else if (addr >= 0xC000 && addr <= 0xCFFF)
			{
				return &ram2_[addr - 0xC000];
			}
			else if (addr >= 0xD000 && addr <= 0xDFFF)
			{
				// TODO: CGB support
				return &switchable_ram2_[0][addr - 0xD000];
			}
			else
			{
				return &ram3_[addr - 0xE000];
			}

			return nullptr;
		}

		virtual void control(uint8_t value, uint16_t addr)
		{
			if (addr >= 0x0000 && addr <= 0x1FFF)
			{
				xram_enable_ = (value == 0x0A);
			}
			else if (addr >= 0x2000 && addr <= 0x3FFF)
			{
				selectRomBank(value);
			}
			else if (addr >= 0x4000 && addr <= 0x5FFF)
			{
				if (mode_ == MemoryMode::ROM)
				{
					rom_idx_upper_bits_ = value & 0x03;
				}
				else
				{
					selectRamBank(value);
				}
			}
			else if (addr >= 0x6000 && addr <= 0x7FFF)
			{
				mode_ = static_cast<MemoryMode>(value);
			}
		}

	private:
		void selectRomBank(uint8_t rom_bank_number)
		{
			auto bank_number = 0u;

			// potentially remap the rom bank number
			switch (rom_bank_number)
			{
			case 0x00:
			case 0x20:
			case 0x40:
			case 0x60:
				bank_number = rom_bank_number + 1;
				break;
			default:
				bank_number = rom_bank_number;
				break;
			}

			rom_idx_ = ((rom_idx_upper_bits_ << 5) | bank_number) - 1;
		}

		void selectRamBank(uint8_t ram_bank_number)
		{
			ram_idx_ = ram_bank_number & 0x03;
		}

		void loadROM(uint8_t* rom, uint32_t size, uint8_t rom_size)
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
			rom0_.resize(0x3FFF - 0x0000 + 1);

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

		void loadRAM(uint8_t ram_size)
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

	private:
		// TODO: these could be protected member of MBC base class
		MBC::Bank  rom0_;            ///< $0000 - $3FFF
		MBC::Banks switchable_rom_;  ///< $4000 - $7FFF
		MBC::Bank  ram1_;            ///< $8000 - $9FFF
		MBC::Banks switchable_ram1_; ///< $A000 - $BFFF
		MBC::Bank  ram2_;            ///< $C000 - $CFFF
		MBC::Banks switchable_ram2_; ///< $D000 - $DFFF (Switchable in CGB mode Only)
		MBC::Bank  ram3_;            ///< $E000 - $FFFF

		unsigned int rom_idx_;
		unsigned int rom_idx_upper_bits_; // bit 5 and 6

		unsigned int ram_idx_;

		MemoryMode mode_;
	};
}

#endif
