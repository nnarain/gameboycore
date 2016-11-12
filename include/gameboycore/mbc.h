
/**
	\author Natesh Narain <nnaraindev@gmail.com>
	\date   Oct 11 2016
*/

#ifndef GAMEBOY_MBC_H
#define GAMEBOY_MBC_H

#include <cstdint>
#include <vector>
#include <memory>

namespace gb
{
	/**
		\brief Memory Bank Controller Interface
	*/
	class MBC
	{
	public:
		enum class Type{
			ROM_ONLY = 0x00,
			MBC1 = 0x01,
			MBC1_RAM = 0x02,
			MBC1_RAM_BAT = 0x03,
			MBC2 = 0x05,
			MBC2_BAT = 0x06,
			ROM_RAM = 0x08,
			ROM_RAM_BAT = 0x09,
			MMM01 = 0x0B,
			MMM01_RAM = 0x0C,
			MMM01_RAM_BAT = 0x0D,
			MBC3_TIME_BAT = 0x0F,
			MBC3_TIME_RAM_BAT = 0x10,
			MBC3 = 0x11,
			MBC3_RAM = 0x12,
			MBC3_RAM_BAT = 0x13,
			MBC4 = 0x15,
			MBC4_RAM = 0x16,
			MBC4_RAM_BAT = 0x17,
			MBC5 = 0x19,
			MBC5_RAM = 0x1A,
			MBC5_RAM_BAT = 0x1B,
			MBC5_RUMBLE = 0x1C,
			MBC5_RUMBLE_RAM = 0x1D,
			MBC5_RUMBLE_RAM_BAT = 0x1E,
			XRAM_ENABLE = 0x0A,   ///< Enable external RAM
			XRAM_BANK_SIZE = 0x1FFF, ///< External RAM banks are 8 KB in size

			/*
			ROM_32KB = 0x00,
			ROM_64KB = 0x01,
			ROM_128KB = 0x02,
			ROM_256KB = 0x03,
			ROM_512KB = 0x04,
			ROM_1MB = 0x05,
			ROM_2MB = 0x06,
			ROM_4MB = 0x07,
			ROM_1_1MB = 0x52,
			ROM_1_2MB = 0x53,
			ROM_1_5MB = 0x54
			*/
		};

		enum class ROM
		{
			KB32  = 0x00,
			KB64  = 0x01,
			KB128 = 0x02,
			KB256 = 0x03,
			KB512 = 0x04,
			MB1   = 0x05,
			MB2   = 0x06,
			MB4   = 0x07,
			MB1_1 = 0x52,
			MB1_2 = 0x53,
			MB1_5 = 0x54
		};

		enum class XRAM
		{
			NONE = 0x00,
			KB2  = 0x01,
			KB8  = 0x02,
			KB32 = 0x03
		};

	public:
		using Ptr = std::unique_ptr<MBC>;

		using Bank  = std::vector<uint8_t>;
		using Banks = std::vector<Bank>;

	public:
		MBC() :
			xram_enable_{false}
		{
		}

		~MBC()
		{
		}

		/* Interface Functions */

		virtual void control(uint8_t value, uint16_t addr) = 0;

		virtual void write(uint8_t value, uint16_t addr) = 0;
		virtual uint8_t read(uint16_t addr) const = 0;

		virtual uint8_t& get(uint16_t addr) = 0;
		virtual uint8_t* getptr(uint16_t addr) = 0;

	protected:
		bool xram_enable_;
	};
}

#endif // GAMEBOY_MBC_H
