/**
    @file catridge_header.h
    @author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef GAMEBOY_CARTINFO_H
#define GAMEBOY_CARTINFO_H

#include <cstdint>

/**
    Structure containing cartridge information, contained in header
*/
struct CartridgeHeader
{
    uint8_t start[4];
    uint8_t nintendo_logo[48];
    char game_title[16];
    //uint8_t cgb_compat;
    uint8_t license[2];
    uint8_t sgb_compat;
    uint8_t type;
    uint8_t rom_size;
    uint8_t ram_size;
    uint8_t destination_code;
    uint8_t old_license;
    uint8_t rom_version;
    uint8_t complement_checksum;
    uint8_t checksum[2];
};

#endif