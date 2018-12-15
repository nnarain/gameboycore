
#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include <vector>
#include <cstdint>
#include <string>
#include <cstring>
#include <tuple>

#include <gameboycore/memorymap.h>

class CodeGenerator 
{
public:
    static constexpr std::size_t KILOBYTE = 1024;
    static constexpr std::size_t BANK_SIZE = 16 * KILOBYTE;

    // Type, Cart ROM, Cart RAM
    using MemInfoTuple = std::tuple<uint8_t, uint8_t, uint8_t>;

    enum class MBC
    {
        NONE,
        MBC1,
        MBC2,
        MBC3,
        MBC5
    };

	CodeGenerator(MBC mbc = MBC::NONE) :
        rom_{},
        address_counter_{ 0x150 }
	{
        allocateRom(mbc);
		fillCartridgeHeader(mbc);
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

	void address(std::size_t address, std::size_t rom_bank = 0)
	{
        if (rom_bank <= 1)
        {
            address_counter_ = address;
        }
        else
        {
            address_counter_ = (address) + ((rom_bank-1) * BANK_SIZE);
        }
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
    void allocateRom(MBC mbc)
    {
        switch (mbc)
        {
        case CodeGenerator::MBC::MBC1:
        case CodeGenerator::MBC::MBC2:
        case CodeGenerator::MBC::MBC3:
        case CodeGenerator::MBC::MBC5:
            rom_.resize(128 * BANK_SIZE);
            break;
        case CodeGenerator::MBC::NONE:
        default:
            rom_.resize(2 * BANK_SIZE);
            break;
        }
    }

	void fillCartridgeHeader(MBC mbc)
	{
        uint8_t type = 0, rom_size = 0, ram_size = 0;
        std::tie(type, rom_size, ram_size) = getMemInfoTuple(mbc);

		rom_[gb::memorymap::CART_TYPE] = type;
		rom_[gb::memorymap::CART_ROM_SIZE] = rom_size;
		rom_[gb::memorymap::CART_RAM_SIZE] = ram_size;

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

    static MemInfoTuple getMemInfoTuple(MBC mbc) noexcept
    {
        switch (mbc)
        {
        case CodeGenerator::MBC::MBC1:
            return std::make_tuple<uint8_t, uint8_t, uint8_t>(0x03, 0x06, 0x03);
        case CodeGenerator::MBC::MBC2:
            return std::make_tuple<uint8_t, uint8_t, uint8_t>(0x06, 0x06, 0x03);
        case CodeGenerator::MBC::MBC3:
            return std::make_tuple<uint8_t, uint8_t, uint8_t>(0x13, 0x06, 0x03);
        case CodeGenerator::MBC::MBC5:
            return std::make_tuple<uint8_t, uint8_t, uint8_t>(0x1B, 0x06, 0x03);
        case CodeGenerator::MBC::NONE:
        default:
            return std::make_tuple<uint8_t, uint8_t, uint8_t>(0x00, 0x00, 0x00);
        }
    }

private:
	std::vector<uint8_t> rom_;
	std::size_t address_counter_;
};

#endif // CODEGENERATOR_H
