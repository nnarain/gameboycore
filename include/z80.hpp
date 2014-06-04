
#ifndef Z80
#define Z80

typedef unsigned char uint8;
typedef signed char int8;

namespace z80{
	
	struct core{
		uint8 A;
		uint8 B;
		uint8 C;
		uint8 D;
		uint8 E;
		uint8 F;

		uint8 H;
		uint8 L;
	};

}

#endif // Z80
