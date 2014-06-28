
#include "com_nnarain_gb_resource_GBROMParser.h"
#include "gbapi.h"

#include <stdlib.h>

/**
	Allocate ROM data
*/
JNIEXPORT jlong JNICALL Java_com_nnarain_gb_resource_GBROMParser_createParser(JNIEnv *env, jclass c)
{
	return (long) ((struct GBROMData*) malloc( sizeof(struct GBROMData) ));
}

JNIEXPORT jint JNICALL Java_com_nnarain_gb_resource_GBROMParser_parse(JNIEnv *env, jclass c, jlong handle, jstring filePath)
{
	struct GBROMData* data = (struct GBROMData*)((long)handle);

	FILE* file;
	const char* path = (*env)->GetStringUTFChars(env, filePath, NULL);

	file = fopen(path, "rb");

	if(file != NULL){

		gbparse(data, file);

		fclose(file);
		return 0;
	}
	else{
		return -1;
	}
}

