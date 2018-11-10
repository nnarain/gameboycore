#ifndef GAMEBOY_ROM_PARSER_H
#define GAMEBOY_ROM_PARSER_H

#include "cartridge_header.hpp"

#include <fstream>

/**
\brief Used to parse rom image for information contained in header
*/
class RomParser
{
public:
    static CartridgeHeader parse(std::ifstream& rom);
};

#endif