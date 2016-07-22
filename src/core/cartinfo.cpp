
#include "gameboy/cartinfo.h"
#include "gameboy/mbc.h"
#include <cstring>

namespace gb
{
    RomParser::RomParser()
    {
    }

    CartInfo RomParser::parse(uint8_t* image)
    {
        CartInfo info;
        info.type = image[memorymap::CART_TYPE];
        info.rom_size = image[memorymap::CART_ROM_SIZE];
        info.ram_size = image[memorymap::CART_RAM_SIZE];
        std::memcpy(
            info.game_title,
            &image[memorymap::GAME_TITLE_START],
            memorymap::GAME_TITLE_END - memorymap::GAME_TITLE_START
        );

        return info;
    }
}
