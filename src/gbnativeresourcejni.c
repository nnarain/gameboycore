
#include "com_nnarain_gb_resource_GBNativeResource.h"
#include <stdlib.h>


JNIEXPORT void JNICALL Java_com_nnarain_gb_resource_GBNativeResource_release(JNIEnv *env, jclass c, jlong handle)
{
	free((void*)((long)handle));
}

