package com.nnarain.gb.map;

public enum GBMemMap{

	PERMANENT_ROM    (0x0000, 0x3FFF),
	NINTENDO_LOGO    (0x0104, 0x0133),
	GAME_TITLE       (0x0134, 0x013E),
	CART_TYPE        (0x0147, 0x0147),
	CART_ROM_SIZE    (0x0148, 0x0148),
	CART_RAM_SIZE    (0x0149, 0x0149),
	SWAP_ROM         (0x4000, 0x7FFF),
	CHARACTER_RAM    (0x8000, 0x97FF),
	BG_MAP_DATA_1    (0x9800, 0x9BFF),
	BG_MAP_DATA_2    (0x9C00, 0x9FFF),
	CART_RAM         (0xA000, 0xBFFF),
	WORK_RAM_BANK_0  (0xC000, 0xCFFF),
	WORK_RAM_BANK_1  (0xD000, 0xDFFF),
	OAM              (0xFE00, 0xFE9F),
	HIGH_RAM         (0xFF80, 0xFFFE),
	INTERRUPT_ENABLE (0xFFFF, 0xFFFF),
	INTERRUPT_FLAG   (0xFF0F, 0xFF0F);

	private final int begin;
	private final int end;
	private final int range;

	GBMemMap(int begin, int end){
		this.begin = begin;
		this.end = end;
		this.range = end - begin;
	}

	public int begin(){
		return this.begin;
	}

	public int end(){
		return this.end;
	}

	public int range(){
		return this.range;
	}

}


