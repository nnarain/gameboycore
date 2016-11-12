/**
    @file cartinfo.h
    @author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef GAMEBOY_CARTINFO_H
#define GAMEBOY_CARTINFO_H

#include "gameboy/memorymap.h"
#include <stdint.h>

namespace gb
{
    /**
        Structure containing cartridge information, contained in header
    */
    struct CartInfo
    {
        uint8_t type;
        uint8_t rom_size;
        uint8_t ram_size;
        char game_title[(memorymap::GAME_TITLE_END - memorymap::GAME_TITLE_START) + 1];
    };

    /**
        \brief Used to parse rom image for information contained in header
    */
    class RomParser
    {
    public:
        RomParser();

        CartInfo parse(uint8_t* image);
    };
}

#endif
