
#ifndef Z80
#define Z80

typedef unsigned char uint8;
typedef signed char int8;

namespace Z80{
	
	struct Core{
		uint8 A; ///< Registers
		uint8 B; ///< Registers
		uint8 C; ///< Registers
		uint8 D; ///< Registers
		uint8 E; ///< Registers
		uint8 F; ///< Registers

		uint8 H; ///< Registers
		uint8 L; ///< Registers

		int* memoryMap;
	};

	void initCore(struct Core core)
	{

	}

}

#endif // Z80
