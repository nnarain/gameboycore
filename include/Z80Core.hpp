
#ifndef Z80
#define Z80

#include <stdlib.h>
#include <cstdint>

#define SIZE_MEMORY_MAP  0xFFFF + 1

#define INTERRUPT_ENABLE 0xFFFF
#define INTERRUPT_FLAG   0xFF0F

namespace Z80{
	
	const long CLK = 4000000; ///< Z80 Clock Speed 4 MHz

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

		uint8_t rom[SIZE_MEMORY_MAP];
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

		// enables V-Blank, LCD Stat, Timer, JoyPad. disable Serial
		core->rom[INTERRUPT_ENABLE] = 0x17;
	}

	uint8_t* getInterruptFlags(Core* core)
	{
		return &core->rom[INTERRUPT_FLAG];
	}

}

#endif // Z80
