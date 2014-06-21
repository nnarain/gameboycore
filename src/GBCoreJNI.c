
#include <stdlib.h>

#include "com_nnarain_gb_GBCore.h"
#include "GBEmulator.h"

JNIEXPORT jlong JNICALL Java_com_nnarain_gb_GBCore_createCore(JNIEnv *env, jclass clazz)
{
	struct Core* core = (struct Core*) malloc( sizeof(struct Core) );
	core->AF.val = 0;
	core->BC.val = 0;
	core->DE.val = 0;
	core->HL.val = 0;
	core->PC = 0;
	core->SP = WORK_RAM_BANK_0_END;

	return (long) core;
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

JNIEXPORT void JNICALL Java_com_nnarain_gb_GBCore_loadROM(JNIEnv *env, jclass c, jlong handle, jcharArray rom)
{
	struct Core* core = (struct Core*) ((long)handle);
	int i;

	const int len = (*env)->GetArrayLength(env, rom);
	jchar* romElements = (*env)->GetCharArrayElements(env, rom, 0);

	for(i = 0; i < len; i++){
		core->rom[i] = (uint8_t) romElements[i];
	}

}

JNIEXPORT void JNICALL Java_com_nnarain_gb_GBCore_swapROM(JNIEnv *env, jclass c, jlong handle, jcharArray rom)
{
	struct Core* core = (struct Core*) ((long)handle);
	int i;
	int j;
	jchar* romElements;

	const int len = SWITCHABLE_ROM_BANK_END - SWITCHABLE_ROM_BANK_START;
	romElements = (*env)->GetCharArrayElements(env, rom, 0);

	for(i = SWITCHABLE_ROM_BANK_START, j = 0; j < len; i++, j++){
		core->rom[i] = romElements[j];
	}
}