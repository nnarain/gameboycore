#include "gameboycore/mbc5.h"

namespace gb
{
	namespace detail
	{
		MBC5::MBC5(uint8_t* rom, uint32_t size, uint8_t rom_size, uint8_t ram_size, bool cgb_enable) : 
			MBC(rom, size, rom_size, ram_size, cgb_enable)
		{
		}

		void MBC5::control(uint8_t value, uint16_t addr)
		{
			if (addr >= 0x0000 && addr <= 0x1FFF)
			{
				xram_enable_ = ((value & 0x0F) == 0x0A);
			}
			else if (addr >= 0x2000 && addr <= 0x2FFF)
			{
				rom_bank_ |= ((rom_bank_ & ~(0xFF)) | value);
			}
			else if (addr >= 0x3000 && addr <= 0x3FFF)
			{
				rom_bank_ |= ((rom_bank_ & ~(0x100)) | ((value & 0xFFFF) << 9));
			}
			else if (addr >= 0x4000 && addr <= 0x5FFF)
			{
				ram_bank_ = value & 0x0F;
			}
		}

		MBC5::~MBC5()
		{
		}
	}
}