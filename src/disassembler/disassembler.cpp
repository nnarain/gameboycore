
/**
	Disassembly a Gameboy ROM file

	@author Natesh Narain <nnaraindev@gmail.com>
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cstdint>
#include <string>
#include <array>
#include <stdexcept>
#include <sstream>

#include <gameboy/opcodeinfo.h>
#include <gameboy/memorymap.h>

using namespace gb;

/**
*/
static std::vector<uint8_t> loadInputFile(const std::string& input);

/**
*/
static void disassembly(const std::vector<uint8_t>& rom, const std::string& output_file);

/**
	@param opcode - current opcode
	@param program_counter - address of the given opcode
*/
static std::string opcodeToAssembly(OpcodeInfo& info, uint16_t& program_counter, const std::vector<uint8_t>& rom);

int main(int argc, char *argv[])
{
	// check input
	if (argc < 3)
	{
		std::cerr << "Usage ./" << argv[0] << " <inputfile> <outputfile>" << std::endl;
		return 1;
	}

	std::string input_file  = std::string(argv[1]);
	std::string output_file = std::string(argv[2]);
	
	try
	{
		// load byte buffer
		std::vector<uint8_t> input_buffer = loadInputFile(input_file);

		// disassembly into list file
		disassembly(input_buffer, output_file);
	}
	catch (std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		return 2;
	}

	return 0;
}

void disassembly(const std::vector<uint8_t>& rom, const std::string& output_file)
{
	// output list file
	std::ofstream list_file(output_file);
	
	// start at address $150
	uint16_t program_counter = 0x0000;
	std::size_t size = rom.size();

	// process every byte in the file
	while (program_counter < size)
	{
		// check if the program counter is in the cartridge header range
		if (program_counter >= 0x0104 && program_counter <= 0x014F)
		{
			// jump to end of cartridge header
			program_counter = 0x0150;
			continue;
		}

		// contain the disassembled string
		std::stringstream line;

		// fetch opcode
		uint8_t opcode = rom[program_counter];
		OpcodePage page = OpcodePage::PAGE1;

		// if page 2 prefix
		if (opcode == 0xCB)
		{
			// fetch extended opcode
			opcode = rom[program_counter + 1];
			page = OpcodePage::PAGE2;
		}

		// get opcode meta data
		OpcodeInfo opcodeinfo = getOpcodeInfo(opcode, page);

		// program counter to line
		line << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << program_counter;
		// disassemble the opcode and operands
		std::string assembly = opcodeToAssembly(opcodeinfo, program_counter, rom);

		// assembly to line
		line << ": " << assembly << std::endl;

		// line to file.
		list_file << line.str();
	}
}

std::string opcodeToAssembly(OpcodeInfo& info, uint16_t& program_counter, const std::vector<uint8_t>& rom)
{
	char str[32];

	// sort through operand types and return disassemblied hair
	if (info.userdata == OperandType::NONE)
	{
		// advance to next line
		program_counter++;
		return std::string(info.disassembly);
	}
	else
	{
		// fetch user depending if 8 bit immediate or 16 bit data
		uint16_t userdata;
		if (info.userdata == OperandType::IMM8)
		{
			userdata = (uint8_t)rom[++program_counter];
		}
		else // OperandType::IMM16
		{
			uint8_t lo = (uint8_t)rom[++program_counter];
			uint8_t hi = (uint8_t)rom[++program_counter];

			userdata = ((hi & 0xFFFF) << 8) | (lo & 0xFFFF);
		}

		program_counter++;

		// format string
		std::sprintf(str, info.disassembly, userdata);

		return std::string(str);
	}
}

std::vector<uint8_t> loadInputFile(const std::string& input)
{
	std::ifstream file(input, std::ios::binary | std::ios::ate);

	if (!file.good()) 
		throw std::runtime_error("Could open file: " + input);

	std::size_t size = (size_t)file.tellg();

	std::vector<uint8_t> buffer;
	buffer.resize(size);

	file.seekg(0, std::ios::beg);

	file.read((char*)&buffer[0], size);

	return std::move(buffer);
}
