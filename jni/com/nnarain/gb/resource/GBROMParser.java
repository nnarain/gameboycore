package com.nnarain.gb.resource;

/**
* Class to parse GameBoy ROM file
* 
* @author Natesh Narain	
*/
public class GBROMParser extends GBNativeResource{

	private String filePath;

	public GBROMParser(String filePath){
		super(createParser());
		this.filePath = filePath;
	}

	/* Native Functions */

	private static native long createParser();

}

