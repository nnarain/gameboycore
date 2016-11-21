#include "gameboycore/mbc.h"

#include <algorithm>
#include <cstring>

namespace gb
{
	namespace detail
	{
		MBC::MBC(uint8_t* rom, uint32_t size, uint8_t rom_size, uint8_t ram_size) :
			xram_enable_(false),
			rom_bank_(0),
			ram_bank_(0),
			num_rom_banks_(0),
			num_ram_banks_(0)
		{
			loadMemory(rom, size, rom_size, ram_size);
		}

		void MBC::write(uint8_t value, uint16_t addr)
		{
			// check for write to ROM
			if (addr <= 0x7FFF)
			{
				control(value, addr);
			}
			else
			{
				// get the memory index from the addr
				auto idx = getIndex(addr);

				// check if writing to external RAM
				if (addr >= 0xA000 && addr <= 0xBFFF)
				{
					// write to external ram if it is enabled
					if (xram_enable_)
						memory_[idx] = value;
				}
				else
				{
					memory_[idx] = value;
				}
			}
		}

		uint8_t MBC::read(uint16_t addr) const
		{
			return memory_[getIndex(addr)];
		}

		uint8_t& MBC::get(uint16_t addr)
		{
			return memory_[getIndex(addr)];
		}

		uint8_t* MBC::getptr(uint16_t addr)
		{
			return &memory_[getIndex(addr)];
		}

		std::vector<uint8_t> MBC::getRange(uint16_t start, uint16_t end) const
		{
			auto start_idx = getIndex(start);
			auto end_idx = getIndex(end);
			return std::vector<uint8_t>(memory_.begin() + start_idx, memory_.begin() + end_idx);
		}

		void MBC::setMemory(uint16_t start, const std::vector<uint8_t>& mem)
		{
			// TODO: error checks
			std::copy(mem.begin(), mem.end(), memory_.begin() + getIndex(start));
		}

		int MBC::getRomBank() const
		{
			return rom_bank_;
		}

		int MBC::getRamBank() const
		{
			return ram_bank_;
		}

		bool MBC::isXramEnabled() const
		{
			return xram_enable_;
		}

		int MBC::getIndex(uint16_t addr) const
		{
			switch (addr & 0xF000)
			{
			case 0x0000:
			case 0x1000:
			case 0x2000:
			case 0x3000:
				return addr;
			case 0x4000:
			case 0x5000:
			case 0x6000:
			case 0x7000:
				return (addr) + ((16 * KILO_BYTE) * rom_bank_);
				break;
			case 0x8000:
			case 0x9000:
				return (addr) + (16 * KILO_BYTE * (num_rom_banks_-1));
			case 0xA000:
			case 0xB000:
				return (addr) + (16 * KILO_BYTE * (num_rom_banks_-1)) + (8 * KILO_BYTE * ram_bank_);
			case 0xC000:
			case 0xD000:
			case 0xE000:
			case 0xF000:
				return (addr) + (16 * KILO_BYTE * (num_rom_banks_-1)) + (8 * KILO_BYTE * (num_ram_banks_-1));
			}

			return 0;
		}

		void MBC::loadMemory(uint8_t* rom, std::size_t size, uint8_t rom_size, uint8_t ram_size)
		{
			// lookup tables for number of ROM banks a cartridge has
			static const unsigned int rom_banks1[] = {
				2, 4, 8, 16, 32, 64, 128, 256
			};
			static const unsigned int rom_banks2[] = {
				72, 80, 96
			};

			if (rom_size <= static_cast<uint8_t>(MBC::ROM::MB4))
			{
				// look up the total number of banks this cartridge has
				auto cartridge_rom_banks = rom_banks1[rom_size];
				// the number of switchable ROM banks is 2 less than the total
				// since there are always 2 available in the $0000 - $3FFF range
				num_rom_banks_ = cartridge_rom_banks - 1;
			}
			else
			{
				// the number of switchable ROM banks is 2 less than the total
				// since there are always 2 available in the $0000 - $3FFF range
				num_rom_banks_ = rom_banks2[rom_size] - 1;
			}

			num_ram_banks_ = (static_cast<MBC::XRAM>(ram_size) == MBC::XRAM::KB32) ? 4 : 1;

			// memory sizes
			const auto rom0             = (16 * KILO_BYTE);
			const auto rom_switchable   = (16 * KILO_BYTE) * num_rom_banks_;
			const auto ram1             = (8 *  KILO_BYTE);
			const auto ram_switchable1  = (8 *  KILO_BYTE) * num_ram_banks_;
			const auto ram2             = (8 *  KILO_BYTE);
			const auto ram_switchable2  = (8 *  KILO_BYTE) * 1; // CGB Only
			const auto ram3             = (8 *  KILO_BYTE);

			const auto memory_size = rom0 + rom_switchable + ram1 + ram_switchable1 + ram2 + ram_switchable2 + ram3;

			memory_.resize(memory_size);

			std::memcpy((char*)&memory_[0], rom, size);
		}

		MBC::~MBC()
		{
		}
	}
}