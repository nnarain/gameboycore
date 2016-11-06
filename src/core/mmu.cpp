
/**
	\author Natesh Narain <nnaraindev@gmail.com>
*/

#include "gameboy/mmu.h"
#include "gameboy/mbc1.h"
#include "bitutil.h"

#include <cstring>
#include <iostream>

static const unsigned int KILO_BYTE = 1024;
static const unsigned int BANK_SIZE = (16 * KILO_BYTE);

namespace gb
{
    MMU::MMU()
    {
    }

    MMU::~MMU()
    {
    }

    void MMU::load(uint8_t* rom, uint32_t size)
    {
		RomParser parser;
		CartInfo header = parser.parse(rom);

		switch (static_cast<MBC::Type>(header.type))
		{
		// Supports MBC1
		// Note: MBC1 handles the ROM only case
		case MBC::Type::ROM_ONLY:
		case MBC::Type::MBC1:
		case MBC::Type::MBC1_RAM:
		case MBC::Type::MBC1_RAM_BAT:
			mbc_.reset(new MBC1(rom, size, header.rom_size, header.ram_size));
			break;

		// TODO: MBC2
		// TODO: MBC3
		// TODO: MBC5

		default:
			throw std::runtime_error("Unsupported cartridge type :(");
			break;
		}

		// initialize joypad keys to not pressed
		mbc_->write(0x0F, memorymap::JOYPAD_REGISTER);
    }

    uint8_t MMU::read(uint16_t addr) const
    {
		return mbc_->read(addr);
    }

	uint8_t MMU::read(uint16_t addr)
	{
		if (addr >= 0xFF00 && addr <= 0xFF7F && read_handlers_[addr - 0xFF00])
		{
			return read_handlers_[addr - 0xFF00]();
		}
		else
		{
			return mbc_->read(addr);
		}
	}

    void MMU::write(uint8_t value, uint16_t addr)
    {
		if (addr == memorymap::DMA_REGISTER)
		{
			oamTransfer(value);
		}
		else if (addr == memorymap::JOYPAD_REGISTER)
		{
			mbc_->write(value | 0x0F, addr);
		}
		else if (addr == memorymap::DIVIDER_REGISER)
		{
			mbc_->write(0, addr);
		}
		else if (addr == memorymap::SC_REGISTER)
		{
			if (value == 0x81)
			{
				std::cout << (char)mbc_->read(memorymap::SB_REGISTER);
			}
		}
		else if (addr >= memorymap::NR10_REGISTER && addr < memorymap::NR52_REGISTER)
		{
			// APU register writes are ignore if the APU is disabled
			auto sound_enable = mbc_->read(memorymap::NR52_REGISTER);

			if (sound_enable & 0x80)
			{
				mbc_->write(value, addr);
			}
		}
		else
		{
			if (addr >= 0xFF00 && addr <= 0xFF7F && write_handlers_[addr - 0xFF00])
			{
				write_handlers_[addr - 0xFF00](value, addr);
			}
			else
			{
				mbc_->write(value, addr);
			}
		}
    }

	void MMU::write(uint16_t value, uint16_t addr)
	{
		uint8_t hi = (value & 0xFF00) >> 8;
		uint8_t lo = (value & 0x00FF);

		write(lo, addr + 0);
		write(hi, addr + 1);
	}

	void MMU::addWriteHandler(uint16_t addr, MemoryWriteHandler handler)
	{
		write_handlers_[addr - 0xFF00] = handler;
	}

	void MMU::addReadHandler(uint16_t addr, MemoryReadHandler handler)
	{
		read_handlers_[addr - 0xFF00] = handler;
	}

	uint8_t& MMU::get(uint16_t addr)
	{
		return mbc_->get(addr);
	}

	uint8_t* MMU::getptr(uint16_t addr)
	{
		return mbc_->getptr(addr);
	}

	void MMU::oamTransfer(uint8_t base)
	{
		// increments of $100 bytes
		uint16_t addr = ((base & 0x00FF) << 8);

		std::memcpy(getptr(memorymap::OAM_START), getptr(addr), memorymap::OAM_END - memorymap::OAM_START);
	}
}
