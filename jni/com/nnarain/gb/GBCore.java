
package com.nnarain.gb;

import com.nnarain.gb.exception.GBRuntimeException;

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
		if(this.isAllocated) 
			release(this.handle);
		else
			throw new GBRuntimeException("Native Resources has already been released");
		this.isAllocated = false;
	}

	/**
	* @return True is native resources for this object is still allocated
	*/
	public boolean isAllocated(){
		return this.isAllocated;
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


