package com.nnarain.gb.util;

import java.io.File;
import java.io.FileInputStream;

import java.io.IOException;
import java.io.FileNotFoundException;

public class GBROMParser{

	public static final int PERMANENT_ROM_BANK_START  = 0x0000;

	public static final int INTERRUPT_HANDLER_VBLANK  = 0x0040;
	public static final int INTERRUPT_HANDLER_LCDSTAT = 0x0048;
	public static final int INTERRUPT_HANDLER_TIMER   = 0x0050;
	public static final int INTERRUPT_HANDLER_SERIAL  = 0x0058;
	public static final int INTERRUPT_HANDLER_JOYPAD  = 0x0060;

	public static final int PROGRAM_START             = 0x0100;

	public static final int NINTENDO_LOGO_START       = 0x0104;
	public static final int NINTENDO_LOGO_END         = 0x0133;

	public static final int GAME_TITLE_START          = 0x0134;
	public static final int GAME_TITLE_END            = 0x013E;

	public static final int GAME_DESTINATION_START    = 0x013F;
	public static final int GAME_DESTINATION_END      = 0x0142;

	public static final int COLOR_COMPATABILITY       = 0x0143;

	public static final int NEW_LICENSE_START         = 0x0144;
	public static final int NEW_LICENSE_END           = 0x0145;

	public static final int SGB_COMPATABILITY         = 0x0146;

	public static final int CART_TYPE                 = 0x0147;

	public static final int CART_ROM_SIZE             = 0x0148;
	public static final int CART_RAM_SIZE             = 0x0149;

	public static final int DETINATION_CODE           = 0x014A;

	public static final int OLD_LICENSE               = 0x014B;

	public static final int MASK_ROM_VERSION          = 0x014C;

	public static final int COMPLEMENT_CHECKSUM       = 0x014D;

	public static final int CHECKSUM_START            = 0x014E;
	public static final int CHECKSUM_END              = 0x014F;

	public static final int PERMANENT_ROM_BANK_END    = 0x3FFF;

	public static final int SWITCHABLE_ROM_BANK_START = 0x4000;
	public static final int SWITCHABLE_ROM_BANK_END   = 0x7FFF;

	public static final int CHARACTER_RAM_START       = 0x8000;
	public static final int CHARACTER_RAM_END         = 0x97FF;

	public static final int BG_MAP_DATA_1_START       = 0x9800;
	public static final int BG_MAP_DATA_1_END         = 0x9BFF;

	public static final int BG_MAP_DATA_2_START       = 0x9C00;
	public static final int BG_MAP_DATA_2_END         = 0x9FFF;

	public static final int CART_RAM_BANK_START       = 0xA000;
	public static final int CART_RAM_BANK_END         = 0xBFFF;

	public static final int WORK_RAM_BANK_0_START     = 0xC000;
	public static final int WORK_RAM_BANK_0_END       = 0xCFFF;

	public static final int WORK_RAM_BANK_1_START     = 0xD000;
	public static final int WORK_RAM_BANK_1_END       = 0xDFFF;

	public static final int OAM_START                 = 0xFE00;
	public static final int OAM_END                   = 0xFE9F;

	public static final int JOYPAD_REGISTER           = 0xFF00;

	public static final int HIGH_RAM_START            = 0xFF80;
	public static final int HIGH_RAM_END              = 0xFFFE;

	public static final int INTERRUPT_ENABLE          = 0xFFFF;
	public static final int INTERRUPT_FLAG            = 0xFF0F;

	private byte[] rom;

	public GBROMParser(String fileName) throws FileNotFoundException, IOException{
		this(new File(fileName));
	}

	public GBROMParser(File romFile) throws FileNotFoundException, IOException{
		this.rom = this.getBytes(romFile);
	}

	private byte[] getBytes(File romFile) throws FileNotFoundException, IOException{

		FileInputStream fis = new FileInputStream(romFile);
		byte[] bytes = new byte[fis.available()];

		fis.read(bytes);

		return bytes;

	}

}

