
#ifndef GAMEBOY_MBC_H
#define GAMEBOY_MBC_H

namespace gb
{
namespace mbc
{
enum{
    ROM_ONLY            = 0x00,
    MBC1                = 0x01,
    MBC1_RAM            = 0x02,
    MBC1_RAM_BAT        = 0x03,
    MBC2                = 0x05,
    MBC2_BAT            = 0x06,
    ROM_RAM             = 0x08,
    ROM_RAM_BAT         = 0x09,
    MMM01               = 0x0B,
    MMM01_RAM           = 0x0C,
    MMM01_RAM_BAT       = 0x0D,
    MBC3_TIME_BAT       = 0x0F,
    MBC3_TIME_RAM_BAT   = 0x10,
    MBC3                = 0x11,
    MBC3_RAM            = 0x12,
    MBC3_RAM_BAT        = 0x13,
    MBC4                = 0x15,
    MBC4_RAM            = 0x16,
    MBC4_RAM_BAT        = 0x17,
    MBC5                = 0x19,
    MBC5_RAM            = 0x1A,
    MBC5_RAM_BAT        = 0x1B,
    MBC5_RUMBLE         = 0x1C,
    MBC5_RUMBLE_RAM     = 0x1D,
    MBC5_RUMBLE_RAM_BAT = 0x1E,
    XRAM_ENABLE         = 0x0A,   ///< Enable external RAM
    XRAM_BANK_SIZE      = 0x1FFF, ///< External RAM banks are 8 KB in size

	ROM_32KB            = 0x00,
	ROM_64KB            = 0x01,
	ROM_128KB           = 0x02,
	ROM_256KB           = 0x03,
	ROM_512KB           = 0x04,
	ROM_1MB             = 0x05,
	ROM_2MB             = 0x06,
	ROM_4MB             = 0x07,
	ROM_1_1MB           = 0x52,
	ROM_1_2MB           = 0x53,
	ROM_1_5MB           = 0x54,

    XRAM_NONE           = 0x00,
    XRAM_2KB            = 0x01,
    XRAM_8KB            = 0x02,
    XRAM_32KB           = 0x03
};
}
}

#endif // GAMEBOY_MBC_H
