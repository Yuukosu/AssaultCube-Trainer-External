#ifndef ASSAULTEXTERNAL_PROCESS_H
#define ASSAULTEXTERNAL_PROCESS_H

#include <Windows.h>
#include <TlHelp32.h>

namespace Process {

    DWORD GetProcessId(const char* processName);
    uintptr_t GetModuleBaseAddress(DWORD processId, const char* processName);
}

#endif //ASSAULTEXTERNAL_PROCESS_H
