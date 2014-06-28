
#include "com_nnarain_gb_resource_GBROMParser.h"
#include "gbapi.h"

JNIEXPORT jlong JNICALL Java_com_nnarain_gb_resource_GBROMParser_createParser(JNIEnv *env, jclass c)
{
	return (long) ((struct GBROMData*) malloc(1 * sizeof(struct GBROMData)));
}

