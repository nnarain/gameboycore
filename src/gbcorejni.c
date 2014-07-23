
#include "com_nnarain_gb_resource_GBCore.h"
#include "gbapi.h"
#include <stdlib.h>

JNIEXPORT jlong JNICALL Java_com_nnarain_gb_resource_GBCore_createCore(JNIEnv *env, jclass clazz)
{
	GBCore* core = (GBCore*) malloc( sizeof(GBCore) );
	initCore(core);

	return (long) core;
}

JNIEXPORT void JNICALL Java_com_nnarain_gb_GBCore_step(JNIEnv *env, jclass clazz, jlong handle)
{
	GBCore* core = (GBCore*) ((long)handle);
	step(core);
}

JNIEXPORT void JNICALL Java_com_nnarain_gb_resource_GBCore_release(JNIEnv *env, jclass clazz, jlong handle)
{
	GBCore* core = (GBCore*) ((long)handle);

	releaseBanks(&core->mbc);
	free(core);
}