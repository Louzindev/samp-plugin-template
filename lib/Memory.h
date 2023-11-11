#ifndef _PLUGIN_MEMORY_H_
#define _PLUGIN_MEMORY_H_

#ifdef _WIN32
#include <Windows.h>
#include <Psapi.h>
#endif

#include <unordered_map>
#include <memory>

bool Unlock(void* address, size_t len);
bool memory_compare(const BYTE* data, const BYTE* pattern, const char* mask);
DWORD FindPattern(char* pattern, char* mask);

#endif