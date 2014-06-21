
#include <stdlib.h>

#include "com_nnarain_gb_GBCore.h"
#include "GBEmulator.h"

JNIEXPORT jlong JNICALL Java_com_nnarain_gb_GBCore_createCore(JNIEnv *env, jclass clazz)
{
	return (long) malloc( sizeof(struct Core) );
}

JNIEXPORT void JNICALL Java_com_nnarain_gb_GBCore_release(JNIEnv *env, jclass clazz, jlong handle)
{
	free( (struct Core*) ((long)handle) );
}

JNIEXPORT void JNICALL Java_com_nnarain_gb_GBCore_step(JNIEnv *env, jclass clazz, jlong handle)
{
	struct Core* core = (struct Core*) ((long)handle);
	execute(core, core->rom[++core->PC]);
}