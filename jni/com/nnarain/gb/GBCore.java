
package com.nnarain.gb;

public class GBCore{

	private final long handle;
	private boolean isAllocated;

	public GBCore(){
		this.handle = createCore();
		this.isAllocated = true;
	}

	public void step(){
		step(this.handle);
	}

	public void loadROMBank0(byte[] rom){
		loadROMBank0(this.handle, rom);
	}

	public void release(){
		release(this.handle);
		this.isAllocated = false;
	}

	@Override
	protected void finalize() throws Throwable{
		if(this.isAllocated) release();
		super.finalize();
	}

	/* Native Functions */

	private static native long createCore();
	private static native void release(long handle);

	private static native void loadROMBank0(long handle, byte[] rom);
	private static native void swapROM(long handle, byte[] rom);

	private static native void step(long handle);

}


