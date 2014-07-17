
#include "com_nnarain_gb_resource_GBROMParser.h"
#include "gbapi.h"

#include <stdlib.h>

/**
	Allocate ROM data
*/
JNIEXPORT jlong JNICALL Java_com_nnarain_gb_resource_GBROMParser_createParser(JNIEnv *env, jclass c)
{
	return 0L;
}

JNIEXPORT jint JNICALL Java_com_nnarain_gb_resource_GBROMParser_parse(JNIEnv *env, jclass c, jlong handle, jstring filePath)
{
	struct Core* core = (struct Core*)((long)handle);

	FILE* file;
	const char* path = (*env)->GetStringUTFChars(env, filePath, NULL);

	file = fopen(path, "rb");

	if(file != NULL){

		gbparse(&core->mbc, file);

		fclose(file);
		return 0;
	}
	else{
		return -1;
	}
}

