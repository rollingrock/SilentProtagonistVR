#pragma once
typedef unsigned long long UInt64;
typedef unsigned long UInt32;
typedef unsigned short UInt16;
typedef unsigned char UInt8;

/*
void SafeWriteBuf(uintptr_t addr, void* data, size_t len)
{
	UInt32	oldProtect;

	VirtualProtect((void*)addr, len, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy((void*)addr, data, len);
	VirtualProtect((void*)addr, len, oldProtect, &oldProtect);
}*/