
#include "gameboy/opcodeinfo.h"

namespace gb
{
	static const OpcodeInfo opcodeinfo1[] = {
		{ 0, "nop"       }, // 0x00
		{ 0, "ld BC,%04X", OperandType::IMM16      }, // 0x01
		{ 0, "ld (BC),A" }, // 0x02
		{ 0, "inc BC"    }, // 0x03
		{ 0, "inc B"    }, // 0x04
		{ 0, "dec B"      }, // 0x05
		{ 0, "ld B,%02X",  OperandType::IMM8     }, // 0x06
		{ 0, "rlca",      }, // 0x07
		{ 0, "ld (%04X)SP", OperandType::IMM16 }, // 0x08
		{ 0, "add HL,BC",  }, // 0x09
		{ 0, "ld A,(BC)", }, // 0x0A
		{ 0, "dec BC"    }, // 0x0B
		{ 0, "inc C"      }, // 0x0C
		{ 0, "dec C"     }, // 0x0D
		{ 0, "ld C,%02X",  OperandType::IMM8 }, // 0x0E
		{ 0, "rrca",       }, // 0x0F

		{ 0, "stop",       }, // 0x10
		{ 0, "ld DE,%04X",   OperandType::IMM16 }, // 0x11
		{ 0, "ld (DE),A",  }, // 0x12
		{ 0, "inc DE",     }, // 0x13
		{ 0, "inc D",      }, // 0x14
		{ 0, "dec D",      }, // 0x15
		{ 0, "ld D,%02X", OperandType::IMM8 }, // 0x16
		{ 0, "rla",        }, // 0x17
		{ 0, "jr %02X", OperandType::IMM8 }, // 0x18
		{ 0, "add HL,DE",  }, // 0x19
		{ 0, "ld A,(DE)",  }, // 0x1A
		{ 0, "dec DE",     }, // 0x1B
		{ 0, "inc E",      }, // 0x1C
		{ 0, "dec E",      }, // 0x1D
		{ 0, "ld E,%02X",  OperandType::IMM8 }, // 0x1E
		{ 0, "rra",        }, // 0x1F

		{ 0, "jr NZ,%02X", OperandType::IMM8      }, // 0x20
		{ 0, "ld HL,%04X",  OperandType::IMM16 }, // 0x21
		{ 0, "ld (HL+),A", }, // 0x22
		{ 0, "inc HL",     }, // 0x23
		{ 0, "inc H",      }, // 0x24
		{ 0, "dec H",      }, // 0x25
		{ 0, "ld H,%02X", OperandType::IMM8 }, // 0x26
		{ 0, "daa",        }, // 0x27
		{ 0, "jr Z,%02X",  OperandType::IMM8 }, // 0x28
		{ 0, "add HL,HL",  }, // 0x29
		{ 0, "ld A,(HL+)", }, // 0x2A
		{ 0, "dec HL",     }, // 0x2B
		{ 0, "inc L",      }, // 0x2C
		{ 0, "dec L",      }, // 0x2D
		{ 0, "ld L,%02X",  OperandType::IMM8 }, // 0x2E
		{ 0, "cpl",        }, // 0x2F

		{ 0, "jr NC,%02X",  OperandType::IMM8 }, // 0x30
		{ 0, "ld SP,%04X", OperandType::IMM16 }, // 0x31
		{ 0, "ld (HL-),A", }, // 0x32
		{ 0, "inc SP",     }, // 0x33
		{ 0, "inc (HL)",    }, // 0x34
		{ 0, "dec (HL)",   }, // 0x35
		{ 0, "ld (HL)", OperandType::IMM8   }, // 0x36
		{ 0, "scf",        }, // 0x37
		{ 0, "jr C,%02X",  OperandType::IMM8 }, // 0x38
		{ 0, "add HL,SP", }, // 0x39
		{ 0, "ld A,(HL-)", }, // 0x3A
		{ 0, "dec SP",     }, // 0x3B
		{ 0, "inc A",      }, // 0x3C
		{ 0, "dec A",      }, // 0x3D
		{ 0, "ld A,%02X", OperandType::IMM8 }, // 0x3E
		{ 0, "ccf",        }, // 0x3F

		{ 0, "ld B,B",     }, // 0x40
		{ 0, "ld B,C",     }, // 0x41
		{ 0, "ld B,D",     }, // 0x42
		{ 0, "ld B,E",     }, // 0x43
		{ 0, "ld B,H",     }, // 0x44
		{ 0, "ld B,L",     }, // 0x45
		{ 0, "ld B,(HL)",  }, // 0x46
		{ 0, "ld B,A",     }, // 0x47
		{ 0, "ld C,B",     }, // 0x48
		{ 0, "ld C,C",     }, // 0x49
		{ 0, "ld C,D",     }, // 0x4A
		{ 0, "ld C,E",     }, // 0x4B
		{ 0, "ld C,H",     }, // 0x4C
		{ 0, "ld C,L",     }, // 0x4D
		{ 0, "ld C,(HL)",  }, // 0x4E
		{ 0, "ld C,A",     }, // 0x4F

		{ 0, "ld D,B",     }, // 0x50
		{ 0, "ld D,C",     }, // 0x51
		{ 0, "ld D,D",     }, // 0x52
		{ 0, "ld D,E",     }, // 0x53
		{ 0, "ld D,H",     }, // 0x54
		{ 0, "ld D,L",     }, // 0x55
		{ 0, "ld D,(HL)",  }, // 0x56
		{ 0, "ld D,A",     }, // 0x57
		{ 0, "ld E,B",     }, // 0x58
		{ 0, "ld E,C",     }, // 0x59
		{ 0, "ld E,D",     }, // 0x5A
		{ 0, "ld E,E",     }, // 0x5B
		{ 0, "ld E,H",     }, // 0x5C
		{ 0, "ld E,L",     }, // 0x5D
		{ 0, "ld E,(HL)",  }, // 0x5E
		{ 0, "ld E,A",     }, // 0x5F

		{ 0, "ld H,B",     }, // 0x60
		{ 0, "ld H,C",     }, // 0x61
		{ 0, "ld H,D",     }, // 0x62
		{ 0, "ld H,E",     }, // 0x63
		{ 0, "ld H,H",     }, // 0x64
		{ 0, "ld H,L",     }, // 0x65
		{ 0, "ld H,(HL)",  }, // 0x66
		{ 0, "ld H,A",     }, // 0x67
		{ 0, "ld L,B",     }, // 0x68
		{ 0, "ld L,C",     }, // 0x69
		{ 0, "ld L,D",     }, // 0x6A
		{ 0, "ld L,E",     }, // 0x6B
		{ 0, "ld L,H",     }, // 0x6C
		{ 0, "ld L,L",     }, // 0x6D
		{ 0, "ld L,(HL)",  }, // 0x6E
		{ 0, "ld L,A",     }, // 0x6F

		{ 0, "ld (HL),B",  }, // 0x70
		{ 0, "ld (HL),C",  }, // 0x71
		{ 0, "ld (HL),D",  }, // 0x72
		{ 0, "ld (HL),E",  }, // 0x73
		{ 0, "ld (HL),H",  }, // 0x74
		{ 0, "ld (HL),L",  }, // 0x75
		{ 0, "halt",       }, // 0x76
		{ 0, "ld (HL),A",  }, // 0x77
		{ 0, "ld A,B",     }, // 0x78
		{ 0, "ld A,C",     }, // 0x79
		{ 0, "ld A,D",     }, // 0x7A
		{ 0, "ld A,E",     }, // 0x7B
		{ 0, "ld A,H",     }, // 0x7C
		{ 0, "ld A,L",     }, // 0x7D
		{ 0, "ld A,(HL)",  }, // 0x7E
		{ 0, "ld A,A",     }, // 0x7F

		{ 0, "add A,B",    }, // 0x80
		{ 0, "add A,C",    }, // 0x81
		{ 0, "add A,D",    }, // 0x82
		{ 0, "add A,E",    }, // 0x83
		{ 0, "add A,H",    }, // 0x84
		{ 0, "add A,L",    }, // 0x85
		{ 0, "add A,(HL)", }, // 0x86
		{ 0, "add A,A",    }, // 0x87
		{ 0, "adc A,B",    }, // 0x88
		{ 0, "adc A,C",    }, // 0x89
		{ 0, "adc A,D",    }, // 0x8A
		{ 0, "adc A,E",    }, // 0x8B
		{ 0, "adc A,H",    }, // 0x8C
		{ 0, "adc A,L",    }, // 0x8D
		{ 0, "adc A,(HL)", }, // 0x8E
		{ 0, "adc A,A",    }, // 0x8F

		{ 0, "sub B",      }, // 0x90
		{ 0, "sub C",      }, // 0x91
		{ 0, "sub D",      }, // 0x92
		{ 0, "sub E",      }, // 0x93
		{ 0, "sub H",      }, // 0x94
		{ 0, "sub L",      }, // 0x95
		{ 0, "sub (HL)",   }, // 0x96
		{ 0, "sub A",      }, // 0x97
		{ 0, "subc A,B",   }, // 0x98
		{ 0, "subc A,C",   }, // 0x99
		{ 0, "subc A,D",   }, // 0x9A
		{ 0, "subc A,E",   }, // 0x9B
		{ 0, "subc A,H",   }, // 0x9C
		{ 0, "subc A,L",   }, // 0x9D
		{ 0, "subc A,(HL)",}, // 0x9E
		{ 0, "subc A,A",   }, // 0x9F

		{ 0, "and B",      }, // 0xA0
		{ 0, "and C",      }, // 0xA1
		{ 0, "and D",      }, // 0xA2
		{ 0, "and E",      }, // 0xA3
		{ 0, "and H",      }, // 0xA4
		{ 0, "and L",      }, // 0xA5
		{ 0, "and (HL)",   }, // 0xA6
		{ 0, "and A",      }, // 0xA7
		{ 0, "xor B",      }, // 0xA8
		{ 0, "xor C",      }, // 0xA9
		{ 0, "xor D",      }, // 0xAA
		{ 0, "xor E",      }, // 0xAB
		{ 0, "xor H",      }, // 0xAC
		{ 0, "xor L",      }, // 0xAD
		{ 0, "xor (HL)",   }, // 0xAE
		{ 0, "xor A",      }, // 0xAF

		{ 0, "or B",       }, // 0xB0
		{ 0, "or C",       }, // 0xB1
		{ 0, "or D",       }, // 0xB2
		{ 0, "or E",       }, // 0xB3
		{ 0, "or H",       }, // 0xB4
		{ 0, "or L",       }, // 0xB5
		{ 0, "or (HL)",    }, // 0xB6
		{ 0, "or A",       }, // 0xB7
		{ 0, "cp B",       }, // 0xB8
		{ 0, "cp C",       }, // 0xB9
		{ 0, "cp D",       }, // 0xBA
		{ 0, "cp E",       }, // 0xBB
		{ 0, "cp H",       }, // 0xBC
		{ 0, "cp L",       }, // 0xBD
		{ 0, "cp (HL)",    }, // 0xBE
		{ 0, "cp A",       }, // 0xBF

		{ 0, "ret NZ",     }, // 0xC0
		{ 0, "pop BC",     }, // 0xC1
		{ 0, "jp NZ,%04X", OperandType::IMM16 }, // 0xC2
		{ 0, "jp %04X",      OperandType::IMM16 }, // 0xC3
		{ 0, "call NZ,%04X",  OperandType::IMM16 }, // 0xC4
		{ 0, "push BC",    }, // 0xC5
		{ 0, "add A,%02X",   OperandType::IMM8 }, // 0xC6
		{ 0, "rst 00",     }, // 0xC7
		{ 0, "ret Z",      }, // 0xC8
		{ 0, "ret",        }, // 0xC9
		{ 0, "jp Z,%04X", OperandType::IMM16 }, // 0xCA
	    {0, "prefix"       }, // 0xCB
		{ 0, "call Z,%04X", OperandType::IMM16 }, // 0xCC
		{ 0, "call %04X",   OperandType::IMM16 }, // 0xCD
		{ 0, "adc A,%02X",  OperandType::IMM8 }, // 0xCE
		{ 0, "rst 08h",    }, // 0xCF

		{ 0, "ret NC",     }, // 0xD0
		{ 0, "pop DE",     }, // 0xD1
		{ 0, "jp NC,%04X", OperandType::IMM16 }, // 0xD2
		{ 0, "invalid"     }, // 0xD3
		{ 0, "call NC,%04X",   OperandType::IMM16 }, // 0xD4
		{ 0, "push DE",    }, // 0xD5
		{ 0, "sub", OperandType::IMM8       }, // 0xD6
		{ 0, "rst 10",      }, // 0xD7
		{ 0, "ret C",      }, // 0xD8
		{ 0, "reti",       }, // 0xD9
		{ 0, "jp C,%04X", OperandType::IMM16 }, // 0xDA
		{ 0, "invalid"     }, // 0xDB
		{ 0, "call C,%04X", OperandType::IMM16 }, // 0xDC
		{ 0, "invalid"     }, // 0xDD
		{ 0, "sbc A,%02X", OperandType::IMM8 }, // 0xDE
		{ 0, "rst 18",     }, // 0xDF

		{ 0, "ldh (%02X),A", OperandType:: IMM8}, // 0xE0
		{ 0, "pop HL",     }, // 0xE1
		{ 0, "ld (C),A",   }, // 0xE2
		{ 0, "invalid"     }, // 0xE3
		{ 0, "invalid"     }, // 0xE4
		{ 0, "push HL",    }, // 0xE5
		{ 0, "and %02X", OperandType::IMM8 }, // 0xE6
		{ 0, "rst 20",     }, // 0xE7
		{ 0, "add SP,%02X",  OperandType::IMM8 }, // 0xE8
		{ 0, "jp (HL)",    }, // 0xE9
		{ 0, "ld (%04X),A", OperandType:: IMM16}, // 0xEA
		{ 0, "invalid"     }, // 0xEB
		{ 0, "invalid"     }, // 0xEC
		{ 0, "invalid"     }, // 0xED
		{ 0, "xor %02X",  OperandType::IMM8 }, // 0xEE
		{ 0, "rst 28",     }, // 0xEF

		{ 0, "ldh A,(%02X)", OperandType::IMM8 }, // 0xF0
		{ 0, "pop AF",      }, // 0xF1
		{ 0, "ld (A),C",    }, // 0xF2
		{ 0, "di",          }, // 0xF3
		{ 0, "invalid"      }, // 0xF4
		{ 0, "push AF",     }, // 0xF5
		{ 0, "or %02X",  OperandType::IMM8 }, // 0xF6
		{ 0, "rst 30",      }, // 0xF7
		{ 0, "ld HL,SP+r8", }, // 0xF8
		{ 0, "ld SP,HL",    }, // 0xF9
		{ 0, "ld A,(%04X)", OperandType::IMM16 }, // 0xFA
		{ 0, "ei",          }, // 0xFB
		{ 0, "invalid"      }, // 0xFC
		{ 0, "invalid"      }, // 0xFD
		{ 0, "cp %02X",  OperandType::IMM8 }, // 0xFE
		{ 0, "rst 38"       }  // 0xFF
	};

	static const OpcodeInfo opcodeinfo2[] = {
		{ 0, "RLC B" },
		{ 0, "RLC C" },
		{ 0, "RLC D" },
		{ 0, "RLC E" },
		{ 0, "RLC H" },
		{ 0, "RLC L" },
		{ 0, "RLC (HL)" },
		{ 0, "RLC A" },

		{ 0, "RRC B" },
		{ 0, "RRC C" },
		{ 0, "RRC D" },
		{ 0, "RRC E" },
		{ 0, "RRC H" },
		{ 0, "RRC L" },
		{ 0, "RRC (HL)" },
		{ 0, "RRC A" },

		{ 0, "RL B" },
		{ 0, "RL C" },
		{ 0, "RL D" },
		{ 0, "RL E" },
		{ 0, "RL H" },
		{ 0, "RL L" },
		{ 0, "RL (HL)" },
		{ 0, "RL A" },

		{ 0, "RR B" },
		{ 0, "RR C" },
		{ 0, "RR D" },
		{ 0, "RR E" },
		{ 0, "RR H" },
		{ 0, "RR L" },
		{ 0, "RR (HL)" },
		{ 0, "RR A" },

		{ 0, "SLA B" },
		{ 0, "SLA C" },
		{ 0, "SLA D" },
		{ 0, "SLA E" },
		{ 0, "SLA H" },
		{ 0, "SLA L" },
		{ 0, "SLA (HL)" },
		{ 0, "SLA A" },

		{ 0, "SRA B" },
		{ 0, "SRA C" },
		{ 0, "SRA D" },
		{ 0, "SRA E" },
		{ 0, "SRA H" },
		{ 0, "SRA L" },
		{ 0, "SRA (HL)" },
		{ 0, "SRA A" },

		{ 0, "SWAP B" },
		{ 0, "SWAP C" },
		{ 0, "SWAP D" },
		{ 0, "SWAP E" },
		{ 0, "SWAP H" },
		{ 0, "SWAP L" },
		{ 0, "SWAP (HL)" },
		{ 0, "SWAP A" },

		{ 0, "SRL B" },
		{ 0, "SRL C" },
		{ 0, "SRL D" },
		{ 0, "SRL E" },
		{ 0, "SRL H" },
		{ 0, "SRL L" },
		{ 0, "SRL (HL)" },
		{ 0, "SRL A" },

		{ 0, "BIT 0,B" },
		{ 0, "BIT 0,C" },
		{ 0, "BIT 0,D" },
		{ 0, "BIT 0,E" },
		{ 0, "BIT 0,H" },
		{ 0, "BIT 0,L" },
		{ 0, "BIT 0,(HL)" },
		{ 0, "BIT 0,A" },

		{ 0, "BIT 1,B" },
		{ 0, "BIT 1,C" },
		{ 0, "BIT 1,D" },
		{ 0, "BIT 1,E" },
		{ 0, "BIT 1,H" },
		{ 0, "BIT 1,L" },
		{ 0, "BIT 1,(HL)" },
		{ 0, "BIT 1,A" },

		{ 0, "BIT 2,B" },
		{ 0, "BIT 2,C" },
		{ 0, "BIT 2,D" },
		{ 0, "BIT 2,E" },
		{ 0, "BIT 2,H" },
		{ 0, "BIT 2,L" },
		{ 0, "BIT 2,(HL)" },
		{ 0, "BIT 2,A" },

		{ 0, "BIT 3,B" },
		{ 0, "BIT 3,C" },
		{ 0, "BIT 3,D" },
		{ 0, "BIT 3,E" },
		{ 0, "BIT 3,H" },
		{ 0, "BIT 3,L" },
		{ 0, "BIT 3,(HL)" },
		{ 0, "BIT 3,A" },

		{ 0, "BIT 4,B" },
		{ 0, "BIT 4,C" },
		{ 0, "BIT 4,D" },
		{ 0, "BIT 4,E" },
		{ 0, "BIT 4,H" },
		{ 0, "BIT 4,L" },
		{ 0, "BIT 4,(HL)" },
		{ 0, "BIT 4,A" },

		{ 0, "BIT 5,B" },
		{ 0, "BIT 5,C" },
		{ 0, "BIT 5,D" },
		{ 0, "BIT 5,E" },
		{ 0, "BIT 5,H" },
		{ 0, "BIT 5,L" },
		{ 0, "BIT 5,(HL)" },
		{ 0, "BIT 5,A" },

		{ 0, "BIT 6,B" },
		{ 0, "BIT 6,C" },
		{ 0, "BIT 6,D" },
		{ 0, "BIT 6,E" },
		{ 0, "BIT 6,H" },
		{ 0, "BIT 6,L" },
		{ 0, "BIT 6,(HL)" },
		{ 0, "BIT 6,A" },

		{ 0, "BIT 7,B" },
		{ 0, "BIT 7,C" },
		{ 0, "BIT 7,D" },
		{ 0, "BIT 7,E" },
		{ 0, "BIT 7,H" },
		{ 0, "BIT 7,L" },
		{ 0, "BIT 7,(HL)" },
		{ 0, "BIT 7,A" },

			//

		{ 0, "RES 0,B" },
		{ 0, "RES 0,C" },
		{ 0, "RES 0,D" },
		{ 0, "RES 0,E" },
		{ 0, "RES 0,H" },
		{ 0, "RES 0,L" },
		{ 0, "RES 0,(HL)" },
		{ 0, "RES 0,A" },

		{ 0, "RES 1,B" },
		{ 0, "RES 1,C" },
		{ 0, "RES 1,D" },
		{ 0, "RES 1,E" },
		{ 0, "RES 1,H" },
		{ 0, "RES 1,L" },
		{ 0, "RES 1,(HL)" },
		{ 0, "RES 1,A" },

		{ 0, "RES 2,B" },
		{ 0, "RES 2,C" },
		{ 0, "RES 2,D" },
		{ 0, "RES 2,E" },
		{ 0, "RES 2,H" },
		{ 0, "RES 2,L" },
		{ 0, "RES 2,(HL)" },
		{ 0, "RES 2,A" },

		{ 0, "RES 3,B" },
		{ 0, "RES 3,C" },
		{ 0, "RES 3,D" },
		{ 0, "RES 3,E" },
		{ 0, "RES 3,H" },
		{ 0, "RES 3,L" },
		{ 0, "RES 3,(HL)" },
		{ 0, "RES 3,A" },

		{ 0, "RES 4,B" },
		{ 0, "RES 4,C" },
		{ 0, "RES 4,D" },
		{ 0, "RES 4,E" },
		{ 0, "RES 4,H" },
		{ 0, "RES 4,L" },
		{ 0, "RES 4,(HL)" },
		{ 0, "RES 4,A" },

		{ 0, "RES 5,B" },
		{ 0, "RES 5,C" },
		{ 0, "RES 5,D" },
		{ 0, "RES 5,E" },
		{ 0, "RES 5,H" },
		{ 0, "RES 5,L" },
		{ 0, "RES 5,(HL)" },
		{ 0, "RES 5,A" },

		{ 0, "RES 6,B" },
		{ 0, "RES 6,C" },
		{ 0, "RES 6,D" },
		{ 0, "RES 6,E" },
		{ 0, "RES 6,H" },
		{ 0, "RES 6,L" },
		{ 0, "RES 6,(HL)" },
		{ 0, "RES 6,A" },

		{ 0, "RES 7,B" },
		{ 0, "RES 7,C" },
		{ 0, "RES 7,D" },
		{ 0, "RES 7,E" },
		{ 0, "RES 7,H" },
		{ 0, "RES 7,L" },
		{ 0, "RES 7,(HL)" },
		{ 0, "RES 7,A" },
			//

		{ 0, "SET 0,B" },
		{ 0, "SET 0,C" },
		{ 0, "SET 0,D" },
		{ 0, "SET 0,E" },
		{ 0, "SET 0,H" },
		{ 0, "SET 0,L" },
		{ 0, "SET 0,(HL)" },
		{ 0, "SET 0,A" },

		{ 0, "SET 1,B" },
		{ 0, "SET 1,C" },
		{ 0, "SET 1,D" },
		{ 0, "SET 1,E" },
		{ 0, "SET 1,H" },
		{ 0, "SET 1,L" },
		{ 0, "SET 1,(HL)" },
		{ 0, "SET 1,A" },

		{ 0, "SET 2,B" },
		{ 0, "SET 2,C" },
		{ 0, "SET 2,D" },
		{ 0, "SET 2,E" },
		{ 0, "SET 2,H" },
		{ 0, "SET 2,L" },
		{ 0, "SET 2,(HL)" },
		{ 0, "SET 2,A" },

		{ 0, "SET 3,B" },
		{ 0, "SET 3,C" },
		{ 0, "SET 3,D" },
		{ 0, "SET 3,E" },
		{ 0, "SET 3,H" },
		{ 0, "SET 3,L" },
		{ 0, "SET 3,(HL)" },
		{ 0, "SET 3,A" },

		{ 0, "SET 4,B" },
		{ 0, "SET 4,C" },
		{ 0, "SET 4,D" },
		{ 0, "SET 4,E" },
		{ 0, "SET 4,H" },
		{ 0, "SET 4,L" },
		{ 0, "SET 4,(HL)" },
		{ 0, "SET 4,A" },

		{ 0, "SET 5,B" },
		{ 0, "SET 5,C" },
		{ 0, "SET 5,D" },
		{ 0, "SET 5,E" },
		{ 0, "SET 5,H" },
		{ 0, "SET 5,L" },
		{ 0, "SET 5,(HL)" },
		{ 0, "SET 5,A" },

		{ 0, "SET 6,B" },
		{ 0, "SET 6,C" },
		{ 0, "SET 6,D" },
		{ 0, "SET 6,E" },
		{ 0, "SET 6,H" },
		{ 0, "SET 6,L" },
		{ 0, "SET 6,(HL)" },
		{ 0, "SET 6,A" },

		{ 0, "SET 7,B" },
		{ 0, "SET 7,C" },
		{ 0, "SET 7,D" },
		{ 0, "SET 7,E" },
		{ 0, "SET 7,H" },
		{ 0, "SET 7,L" },
		{ 0, "SET 7,(HL)" },
		{ 0, "SET 7,A" },

	};

	OpcodeInfo getOpcodeInfo(uint8_t opcode, OpcodePage page)
	{
		if (page == OpcodePage::PAGE1)
		{
			return opcodeinfo1[opcode];
		}
		else // page == OpcodePage::PAGE2
		{
			return opcodeinfo2[opcode];
		}
	}
}
