
package com.nnarain.gb;

public class GBCore{

	private final long handle;

	public GBCore(){
		this.handle = createCore();
	}

	public void step(){
		step(this.handle);
	}

	public void loadROM(byte[] rom){
		loadROM(this.handle, rom);
	}

	public void release(){
		release(this.handle);
	}

	/* Native Functions */

	private static native long createCore();
	private static native void release(long handle);

	private static native void loadROM(long handle, byte[] rom);
	private static native void swapROM(long handle, byte[] rom);

	private static native void step(long handle);

}


