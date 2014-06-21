
package com.nnarain.gb;

public class GBCore{

	public static final String UNIX_LIB_NAME = "libGBCore.so";

	private long handle;

	public GBCore(){
		this.handle = GBCore.createCore();
	}

	public void step(){
		GBCore.step(this.handle);
	}

	public void release(){
		GBCore.release(this.handle);
	}

	/* Native Functions */

	private static native long createCore();
	private static native void release(long handle);

	private static native void step(long handle);

}


