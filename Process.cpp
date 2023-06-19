#include "Process.h"

DWORD Process::GetProcessId(const char* processName) {
    DWORD processId = -1;
    HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (handle != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 entry;
        entry.dwSize = sizeof(entry);

        if (Process32First(handle, &entry)) {
            while (Process32Next(handle, &entry)) {
                if (!_stricmp(entry.szExeFile, processName)) {
                    processId = entry.th32ProcessID;
                    break;
                }
            }
        }
    }

    CloseHandle(handle);
    return processId;
}

uintptr_t Process::GetModuleBaseAddress(DWORD processId, const char* processName) {
    uintptr_t moduleBaseAddress = -1;
    HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);

    if (handle != INVALID_HANDLE_VALUE) {
        MODULEENTRY32 entry;
        entry.dwSize = sizeof(entry);

        if (Module32First(handle, &entry)) {
            while (Module32Next(handle, &entry)) {
                if (!_stricmp(entry.szModule, processName)) {
                    moduleBaseAddress = (uintptr_t) entry.modBaseAddr;
                    break;
                }
            }
        }
    }

    CloseHandle(handle);
    return moduleBaseAddress;
}
