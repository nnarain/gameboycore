
/**
	Z80Core.hpp

	Define the Gameboy processor structure

	@author Natesh Narain
	@since June 5, 2014
*/

#ifndef GB_CORE
#define GB_CORE

#include <cstdint>

#define SIZE_MEMORY_MAP              0xFFFF + 1

#define PERMANENT_ROM_BANK_START     0x0000
#define PERMANENT_ROM_BANK_END       0x3FFF

#define SWITCHABLE_ROM_BANK_START    0x4000
#define SWITCHABLE_ROM_BANK_END      0x7FFF

#define VRAM_START                   0x8000
#define VRAM_END                     0x9FFF

#define EXTERNAL_RAM_BANK_START      0xA000
#define EXTERNAL_RAM_BANK_END        0xBFFF

#define WORK_RAM_BANK_0_START        0xC000
#define WORK_RAM_BANK_0_END          0xCFFF

#define WORK_RAM_BANK_1_START        0xD000
#define WORK_RAM_BANK_1_END          0xDFFF

#define SPRITE_ATTRIBUTE_TABLE_START 0xFE00
#define SPRITE_ATTRIBUTE_TABLE_END   0xFEFF

#define DEVICE_MAP_START             0xFF00
#define DEVICE_MAP_END               0xFF7F

#define HIGH_RAM_START               0xFF80
#define HIGH_RAM_END                 0xFFFE

#define INTERRUPT_ENABLE             0xFFFF
#define INTERRUPT_FLAG               0xFF0F

#ifdef __cplusplus
namespace gb{
#endif // __cplusplus
	
	const long CLK = 4000000; ///< Z80 Clock Speed 4 MHz

	//! Structure representing the Z80 internals
	typedef struct Core{

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

		uint8_t rom[SIZE_MEMORY_MAP]; ///< Memory

		/* Interrupt Handlers */
		void (*iVBlank)();  ///< V-Blank interrupt handler
		void (*iLCDStat)(); ///< LCD Stat interrupt handler 
		void (*iTimer)();   ///< Timer interrupt handler
		void (*iSerial)();  ///< Serial interrupt handler
		void (*iJoyPad)();  ///< JoyPad interrupt handler
	};

	/**
		Initialize all registers to 0
	*/
	static void initCore(Core* core)
	{
		core->AF.val = 0;
		core->BC.val = 0;
		core->DE.val = 0;
		core->HL.val = 0;
		core->PC     = 0;
		core->SP     = 0; // maybe change?
		core->IX     = 0;
		core->IY     = 0;
	}

	void bootCore(Core* core)
	{
		initCore(core);

		// Default: enables V-Blank, LCD Stat, Timer, JoyPad. disable Serial
		core->rom[INTERRUPT_ENABLE] = 0x17;
	}

	/**
		Return the address of the Interrupt Flags Register

		@param core
			The Z80 Core

		@return address to the interrupt flags register
	*/
	uint8_t* getInterruptFlags(Core* core)
	{
		return &core->rom[INTERRUPT_FLAG];
	}

	/**
		Return the address of the Interrupt Enable Register

		@param core
			The Z80 Core

		@return address to interrupt enable register
	*/
	uint8_t* getInterruptEnable(Core* core)
	{
		return &core->rom[INTERRUPT_ENABLE];
	}

#ifdef __cplusplus
}
#endif

#endif // Z80
