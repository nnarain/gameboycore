package com.nnarain.gb.resource;

import com.nnarain.gb.exception.GBException;

import java.io.FileNotFoundException;

/**
* Class to parse GameBoy ROM file
* 
* @author Natesh Narain	
*/
public class GBROMParser {

	private String filePath;

	public GBROMParser(){
		this(null);
	}

	public GBROMParser(String filePath){
		//super(createParser());
		this.filePath = filePath;
	}

	/**
		Parse the file
	*/
	public void parse(GBCore core) throws GBException{
		if(parse(core.getHandle(), filePath) == -1)
			throw new GBException("error opening file");
	}

	/**
		@param filePath
			path to set
	*/
	public void setFilePath(String filePath){
		this.filePath = filePath;
	}

	/* Native Functions */

	//private static native long createParser();
	private static native int parse(long handle, String filePath);

}

