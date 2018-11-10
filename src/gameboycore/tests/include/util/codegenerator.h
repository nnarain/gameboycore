
#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include <vector>
#include <cstdint>
#include <string>
#include <cstring>
#include <iostream>

#include <gameboycore/memorymap.h>

class CodeGenerator 
{
public:
	CodeGenerator() :
		rom_(32 * 1024), // allocate 2 ROM banks
		address_counter_(0x150)
	{
		fillCartridgeHeader();
	}

	template<typename... Args> 
	void block(Args... args)
	{
		emit(args...);
	}

	template<typename T, typename... Args>
	void emit(T t, Args... args)
	{
		emit((uint8_t)t);
		emit(args...);
	}

	void emit(uint8_t byte)
	{
		rom_[address_counter_++] = byte;
	}

	void emit()
	{
		// end of block
	}

	void address(uint16_t address)
	{
		address_counter_ = address;
	}

	void reset()
	{
		address_counter_ = 0x150;
	}
	
	std::vector<uint8_t>& rom()
	{
		return rom_;
	}

private:
	void fillCartridgeHeader()
	{
		// for now these aren't configurable
		// set ROM only, 32kB ROM, no cartridge RAM
		rom_[gb::memorymap::CART_TYPE] = 0;
		rom_[gb::memorymap::CART_ROM_SIZE] = 0;
		rom_[gb::memorymap::CART_RAM_SIZE] = 0;

		// game title
		static const char* game_title = "TEST";
		std::memcpy(&rom_[gb::memorymap::GAME_TITLE_START], game_title, std::strlen(game_title));

		// nintendo logo
		static const uint8_t nintendo_logo[] = {
			0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83,
			0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6,
			0xDD, 0xDD, 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F,
			0xBB, 0xB9, 0x33, 0x3E
		};

		std::memcpy(&rom_[gb::memorymap::NINTENDO_LOGO_START], nintendo_logo, gb::memorymap::NINTENDO_LOGO_END - gb::memorymap::NINTENDO_LOGO_START);

		// program start up
		static const uint8_t program_boot[] = {
			0x00,            // nop
			0xC3, 0x50, 0x01 // jp $150
		};

		std::memcpy(&rom_[gb::memorymap::PROGRAM_START], program_boot, sizeof(program_boot));
	}

private:
	std::vector<uint8_t> rom_;
	uint16_t address_counter_;
};

#endif // CODEGENERATOR_H
