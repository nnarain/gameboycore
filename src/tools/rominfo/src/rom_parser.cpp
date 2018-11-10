#include "rom_parser.hpp"
#include <cstring>

CartridgeHeader RomParser::parse(std::ifstream& rom)
{
    CartridgeHeader header;

    rom.seekg(0x100, std::ios::beg);
    rom.read((char*)&header, sizeof(CartridgeHeader));

    return header;
}