
package com.nnarain.gb;

/**
* Native interface to the underlying C struct Core
*
* @author Natesh Narain
**/
public class GBCore{

	/** Handle to the native structure */
	private final long handle;
	/** flag to check if native resources are allocated */
	private boolean isAllocated;

	/**
	* Allocates native resources
	*/
	public GBCore(){
		this.handle = createCore();
		this.isAllocated = true;
	}

	/**
	* Executes the next instruction
	*/
	public void step(){
		step(this.handle);
	}

	/**
	* Loads the permament ROM Bank of GBCore
	*/
	public void loadROMBank0(byte[] rom){
		loadROMBank0(this.handle, rom);
	}

	/**
	* Frees native resources
	*/
	public void release(){
		release(this.handle);
		this.isAllocated = false;
	}

	/**
	* Free native resources if object get garbage collected
	**/
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


