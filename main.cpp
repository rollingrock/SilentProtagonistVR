#include <Windows.h>
#include "main.h"

#include "f4se_common/f4se_version.h"  // RUNTIME_VERSION
#include "f4se/PluginAPI.h"
#include "f4sE_common/Relocation.h"
#include "F4SE_common/SafeWrite.h"
#include "F4SE_common/BranchTrampoline.h"



extern "C" {  
	const char* SilentFile = "data\\sound\\voice\\xxx_placeholder_silence.wav";
	uintptr_t pModuleBase = 0;
	float minusOne = -1.0;
	int minusOne32Int = 0;
	void* __fastcall HookSilentGetter(void);
	void* __fastcall HookVoiceDuration(void); 
	void* __fastcall HookAnotherOneOfTheseFucks(void);
}


RelocAddr<uintptr_t> hookStartOfFunc(0xde2cf0);


bool F4SEPlugin_Query(const F4SEInterface* f4se, PluginInfo* pluginInfo) {
	pluginInfo->name = "SilentProtagonistF4SEVR";
	pluginInfo->infoVersion = PluginInfo::kInfoVersion;
	if (f4se->isEditor) {
		return false;
	}
	if (f4se->runtimeVersion < RUNTIME_VR_VERSION_1_2_72) {
		return false; //no workie
	}

	return true;
}

void hookSilentGetterWrapper() {
	HookSilentGetter();
	return;
}


bool F4SEPlugin_Load(const F4SEInterface* f4se) {
	//Submit patches.
	pModuleBase = (uintptr_t) GetModuleHandleA(NULL);
	
	//SafeWriteCall(pModuleBase + 0xD9207E,(uintptr_t) HookSilentGetter);
	//char HookBuf[] = "\x4C\x89\x4C\x24\x20\x48\x3B\x0D\x46\x4F\xC4\x04\x75\x09\x31\xD2\xEB\x05\xEB\xEC\x90\x90\x90";
	//SafeWriteBuf(pModuleBase + 0xD9207E, HookBuf, sizeof(HookBuf) - 1);


	if (!g_branchTrampoline.Create(1024 * 64))
	{
		return false;
	}

	g_branchTrampoline.Write5Call(hookStartOfFunc.GetUIntPtr(), (uintptr_t)&hookSilentGetterWrapper);

	SafeWriteBuf(pModuleBase + 0xde2e78, (void*)"\x50\x48\xB8", 0x3);
	SafeWrite64(pModuleBase + 0xde2e7B, (UInt64)HookVoiceDuration);
	SafeWriteBuf(pModuleBase + 0xde2e83, (void*)"\xFF\xD0\x58\x90\x90\x90\x90\x90\x90", 0x9);

	SafeWriteBuf(pModuleBase + 0xde45cb, (void*)"\x48\xB8", 0x2);
	SafeWrite64(pModuleBase + 0xde45cd, (UInt64)HookAnotherOneOfTheseFucks);
	SafeWriteBuf(pModuleBase + 0xde45d5, (void*)"\xFF\xD0\x90\x90\x90\x90", 0x6);

	return true;
}

