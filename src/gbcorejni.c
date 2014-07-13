
#include "com_nnarain_gb_resource_GBCore.h"
#include "gbapi.h"
#include <stdlib.h>

JNIEXPORT jlong JNICALL Java_com_nnarain_gb_resource_GBCore_createCore(JNIEnv *env, jclass clazz)
{
	struct Core* core = (struct Core*) malloc( sizeof(struct Core) );
	initCore(core);

	return (long) core;
}

JNIEXPORT void JNICALL Java_com_nnarain_gb_GBCore_step(JNIEnv *env, jclass clazz, jlong handle)
{
	struct Core* core = (struct Core*) ((long)handle);
	step(core);
}

JNIEXPORT void JNICALL Java_com_nnarain_gb_resource_GBCore_release(JNIEnv *env, jclass clazz, jlong handle)
{
	struct Core* core = (struct Core*) ((long)handle);

	releaseBanks(&core->mbc);
	free(core);
}