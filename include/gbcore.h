
/**
	Define the Gameboy processor structure

	@author Natesh Narain
	@since June 5, 2014
*/

#ifndef GB_CORE
#define GB_CORE

#include <stdint.h>


#define SIZE_MEMORY_MAP           0xFFFF + 1

#define PERMANENT_ROM_BANK_START  0x0000

#define INTERRUPT_HANDLER_VBLANK  0x0040
#define INTERRUPT_HANDLER_LCDSTAT 0x0048
#define INTERRUPT_HANDLER_TIMER   0x0050
#define INTERRUPT_HANDLER_SERIAL  0x0058
#define INTERRUPT_HANDLER_JOYPAD  0x0060

#define PROGRAM_START             0x0100

#define NINTENDO_LOGO_START       0x0104
#define NINTENDO_LOGO_END         0x0133

#define GAME_TITLE_START          0x0134
#define GAME_TITLE_END            0x013E

#define GAME_DESTINATION_START    0x013F
#define GAME_DESTINATION_END      0x0142

#define COLOR_COMPATABILITY       0x0143

#define NEW_LICENSE_START         0x0144
#define NEW_LICENSE_END           0x0145

#define SGB_COMPATABILITY         0x0146

#define CART_TYPE                 0x0147

#define CART_ROM_SIZE             0x0148
#define CART_RAM_SIZE             0x0149

#define DETINATION_CODE           0x014A

#define OLD_LICENSE               0x014B

#define MASK_ROM_VERSION          0x014C

#define COMPLEMENT_CHECKSUM       0x014D

#define CHECKSUM_START            0x014E
#define CHECKSUM_END              0x014F

#define PERMANENT_ROM_BANK_END    0x3FFF

#define SWITCHABLE_ROM_BANK_START 0x4000
#define SWITCHABLE_ROM_BANK_END   0x7FFF

#define CHARACTER_RAM_START       0x8000
#define CHARACTER_RAM_END         0x97FF

#define BG_MAP_DATA_1_START       0x9800
#define BG_MAP_DATA_1_END         0x9BFF

#define BG_MAP_DATA_2_START       0x9C00
#define BG_MAP_DATA_2_END         0x9FFF

#define CART_RAM_BANK_START       0xA000
#define CART_RAM_BANK_END         0xBFFF

#define WORK_RAM_BANK_0_START     0xC000
#define WORK_RAM_BANK_0_END       0xCFFF

#define WORK_RAM_BANK_1_START     0xD000
#define WORK_RAM_BANK_1_END       0xDFFF

#define OAM_START                 0xFE00
#define OAM_END                   0xFE9F

#define JOYPAD_REGISTER           0xFF00

#define HIGH_RAM_START            0xFF80
#define HIGH_RAM_END              0xFFFE

#define INTERRUPT_ENABLE          0xFFFF
#define INTERRUPT_FLAG            0xFF0F

#define SIZE_BANK                 PERMANENT_ROM_BANK_END - PERMANENT_ROM_BANK_START

/* Device I/O */
#define JOYPAD_P10                0x00
#define JOYPAD_P11                0x02
#define JOYPAD_P12                0x04
#define JOYPAD_P13                0x08
#define JOYPAD_P14                0x10
#define JOYPAD_P15                0x20

#define CLK                       4000000UL
#define CLK_PERIOD                1.0f/CLK
	
#define FLAG_C 4
#define FLAG_H 5
#define FLAG_S 6
#define FLAG_Z 7

//! Structure representing the Gameboy internals
struct Core{

	//! 16 bit accumulator
	union{
		struct{
			uint8_t A; ///< All Purpose Register
			uint8_t F; ///< Flag Purpose Register
		};
		int val;
	}AF;
	
	//! 16 bit accumulator
	union{
		struct{
			uint8_t B; ///< All Purpose Register
			uint8_t C; ///< All Purpose Register
		};
		int val;
	}BC;
	
	//! 16 bit accumulator
	union{
		struct{
			uint8_t D; ///< All Purpose Register
			uint8_t E; ///< All Purpose Register
		};
		int val;
	}DE;
	
	//! 16 bit accumulator
	union{
		struct{
			uint8_t H; ///< All Purpose Register
			uint8_t L; ///< All Purpose Register
		};
		int val;
	}HL;

	uint16_t PC; ///< Program Counter
	uint16_t SP; ///< Stack Pointer
	uint16_t IX; ///< Index register X
	uint16_t IY; ///< Index Register Y

	uint8_t mem[SIZE_MEMORY_MAP]; ///< Memory

	uint8_t** banks; ///< ROM Banks. Holds ROM data that can be used for swap rom
};


#endif
