
/**
	\author Natesh Narain <nnaraindev@gmail.com>
*/

#include "gameboycore/mmu.h"
#include "gameboycore/mbc1.h"
#include "bitutil.h"

#include "gameboycore/mbc.h"
#include "gameboycore/cartinfo.h"

#include <cstring>
#include <array>
#include <iostream>

static const unsigned int KILO_BYTE = 1024;
static const unsigned int BANK_SIZE = (16 * KILO_BYTE);

namespace gb
{
	/* Private Interface */

	class MMU::Impl
	{
	public:
		Impl()
		{
		}

		~Impl()
		{
		}

		void load(uint8_t* rom, uint32_t size)
		{
			RomParser parser;
			CartInfo header = parser.parse(rom);

			switch (static_cast<detail::MBC::Type>(header.type))
			{
			// Supports MBC1
			// Note: MBC1 handles the ROM only case
			case detail::MBC::Type::ROM_ONLY:
			case detail::MBC::Type::MBC1:
			case detail::MBC::Type::MBC1_RAM:
			case detail::MBC::Type::MBC1_RAM_BAT:
				mbc_.reset(new detail::MBC1(rom, size, header.rom_size, header.ram_size));
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

			loadResetValues();
			initWriteMasks();
		}
	
		uint8_t read(uint16_t addr)
		{
			if (addr >= 0xFF00 && addr <= 0xFF7F && read_handlers_[addr - 0xFF00])
			{
				return read_handlers_[addr - 0xFF00]();
			}
			else
			{
				auto value = mbc_->read(addr);

				if (addr >= memorymap::NR10_REGISTER && addr <= memorymap::WAVE_PATTERN_RAM_END)
				{
					value |= apu_read_masks[addr - 0xFF00];
				}

				return value;
			}
		}

		void write(uint8_t value, uint16_t addr)
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

		void write(uint16_t value, uint16_t addr)
		{
			uint8_t hi = (value & 0xFF00) >> 8;
			uint8_t lo = (value & 0x00FF);

			write(lo, addr + 0);
			write(hi, addr + 1);
		}

		void oamTransfer(uint8_t base)
		{
			// increments of $100 bytes
			uint16_t addr = ((base & 0x00FF) << 8);

			std::memcpy(mbc_->getptr(memorymap::OAM_START), mbc_->getptr(addr), memorymap::OAM_END - memorymap::OAM_START);
		}

		void loadResetValues()
		{
			// load reset values into registers
			mbc_->write(0x00, memorymap::TIMER_COUNTER_REGISTER);
			mbc_->write(0x00, memorymap::TIMER_MODULO_REGISTER);
			mbc_->write(0x00, memorymap::TIMER_CONTROLLER_REGISTER);

			mbc_->write(0x80, memorymap::NR10_REGISTER);
			mbc_->write(0xBF, memorymap::NR11_REGISTER);
			mbc_->write(0xF3, memorymap::NR12_REGISTER);
			mbc_->write(0xBF, memorymap::NR14_REGISTER);
			mbc_->write(0x3F, memorymap::NR21_REGISTER);
			mbc_->write(0x00, memorymap::NR22_REGISTER);
			mbc_->write(0xBF, memorymap::NR24_REGISTER);
			mbc_->write(0x7F, memorymap::NR30_REGISTER);
			mbc_->write(0xFF, memorymap::NR31_REGISTER);
			mbc_->write(0x9F, memorymap::NR32_REGISTER);
			mbc_->write(0xBF, memorymap::NR33_REGISTER);
			mbc_->write(0xFF, memorymap::NR41_REGISTER);
			mbc_->write(0x00, memorymap::NR42_REGISTER);
			mbc_->write(0x00, memorymap::NR43_REGISTER);
			mbc_->write(0xBF, memorymap::NR44_REGISTER);
			mbc_->write(0x77, memorymap::NR50_REGISTER);
			mbc_->write(0xF3, memorymap::NR51_REGISTER);
			mbc_->write(0xF1, memorymap::NR52_REGISTER); // TODO: super gameboy mode

			mbc_->write(0x91, memorymap::LCDC_REGISTER);
			mbc_->write(0x00, memorymap::SCY_REGISTER);
			mbc_->write(0x00, memorymap::SCX_REGISTER);
			mbc_->write(0x00, memorymap::LYC_REGISTER);
			mbc_->write(0xFC, memorymap::BGP_REGISTER);
			mbc_->write(0xFF, memorymap::OBP0_REGISTER);
			mbc_->write(0xFF, memorymap::OBP1_REGISTER);
			mbc_->write(0x00, memorymap::WX_REGISTER);
			mbc_->write(0x00, memorymap::WY_REGISTER);
			mbc_->write(0x00, memorymap::INTERRUPT_ENABLE);
		}

		void initWriteMasks()
		{
			// NR10 - NR14
			apu_read_masks[0x10] = 0x80;
			apu_read_masks[0x11] = 0x3F;
			apu_read_masks[0x12] = 0x00;
			apu_read_masks[0x13] = 0xFF;
			apu_read_masks[0x14] = 0xBF;

			// NR20 - NR24
			apu_read_masks[0x15] = 0xFF;
			apu_read_masks[0x16] = 0x3F;
			apu_read_masks[0x17] = 0x00;
			apu_read_masks[0x18] = 0xFF;
			apu_read_masks[0x19] = 0xBF;

			// NR30 - NR34
			apu_read_masks[0x1A] = 0x7F;
			apu_read_masks[0x1B] = 0xFF;
			apu_read_masks[0x1C] = 0x9F;
			apu_read_masks[0x1D] = 0xFF;
			apu_read_masks[0x1E] = 0xBF;

			// NR40 - NR44
			apu_read_masks[0x1F] = 0xFF;
			apu_read_masks[0x20] = 0xFF;
			apu_read_masks[0x21] = 0x00;
			apu_read_masks[0x22] = 0x00;
			apu_read_masks[0x23] = 0xBF;

			// NR50 - NR52
			apu_read_masks[0x24] = 0x00;
			apu_read_masks[0x25] = 0x00;
			apu_read_masks[0x26] = 0x70;

			//
			apu_read_masks[0x27] = 0xFF;
			apu_read_masks[0x28] = 0xFF;
			apu_read_masks[0x29] = 0xFF;
			apu_read_masks[0x2A] = 0xFF;
			apu_read_masks[0x2B] = 0xFF;
			apu_read_masks[0x2C] = 0xFF;
			apu_read_masks[0x2D] = 0xFF;
			apu_read_masks[0x2E] = 0xFF;
			apu_read_masks[0x2F] = 0xFF;

			// wave ram
			apu_read_masks[0x30] = 0x00;
			apu_read_masks[0x31] = 0x00;
			apu_read_masks[0x32] = 0x00;
			apu_read_masks[0x33] = 0x00;
			apu_read_masks[0x34] = 0x00;
			apu_read_masks[0x35] = 0x00;
			apu_read_masks[0x36] = 0x00;
			apu_read_masks[0x37] = 0x00;
			apu_read_masks[0x38] = 0x00;
			apu_read_masks[0x39] = 0x00;
			apu_read_masks[0x3A] = 0x00;
			apu_read_masks[0x3B] = 0x00;
			apu_read_masks[0x3C] = 0x00;
			apu_read_masks[0x3D] = 0x00;
			apu_read_masks[0x3E] = 0x00;
			apu_read_masks[0x3F] = 0x00;
		}

	public:
		detail::MBC::Ptr mbc_;

		std::array<MemoryWriteHandler, 0x80> write_handlers_;
		std::array<MemoryReadHandler, 0x80>  read_handlers_;

		std::array<uint8_t, 0x80> apu_read_masks;
	};


	/* Public Interface */

    MMU::MMU() :
		impl_(new Impl)
    {
    }

    MMU::~MMU()
    {
		delete impl_;
    }

    void MMU::load(uint8_t* rom, uint32_t size)
    {
		impl_->load(rom, size);
    }

    uint8_t MMU::read(uint16_t addr) const
    {
		return impl_->mbc_->read(addr);
    }

	uint8_t MMU::read(uint16_t addr)
	{
		return impl_->read(addr);
	}

    void MMU::write(uint8_t value, uint16_t addr)
    {
		impl_->write(value, addr);
    }

	void MMU::write(uint16_t value, uint16_t addr)
	{
		impl_->write(value, addr);
	}

	void MMU::addWriteHandler(uint16_t addr, MemoryWriteHandler handler)
	{
		impl_->write_handlers_[addr - 0xFF00] = handler;
	}

	void MMU::addReadHandler(uint16_t addr, MemoryReadHandler handler)
	{
		impl_->read_handlers_[addr - 0xFF00] = handler;
	}

	uint8_t& MMU::get(uint16_t addr)
	{
		return impl_->mbc_->get(addr);
	}

	uint8_t* MMU::getptr(uint16_t addr)
	{
		return impl_->mbc_->getptr(addr);
	}
}
