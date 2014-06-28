
package com.nnarain.gb.resource;

import com.nnarain.gb.exception.GBRuntimeException;

/**
	Base representation of a Native resource
*/
public class GBNativeResource{

	/** Handle to the native resource */
	protected final long handle;
	/** Flag to check if native resources are still allocated */
	protected boolean isAllocated;

	/**
		@param handle
			handle to native resources
	*/
	public GBNativeResource(long handle){
		this.handle = handle;
		this.isAllocated = true;
	}

	/**
		Calls a native function to release native resources
	*/
	public void release(){
		if(this.isAllocated)
			release(handle);
		else
			throw new GBRuntimeException("Native resources have already been freed");
		isAllocated = false;
	}

	/** @return the native allocated flag */
	public boolean isAllocated(){
		return isAllocated;
	}

	/**
		Free still allocated native resources if the object is garbage collected
	*/
	@Override
	protected void finalize() throws Throwable{
		if(isAllocated) release();
		super.finalize();
	}

	/* Native Function */

	private static native void release(long handle);

}

