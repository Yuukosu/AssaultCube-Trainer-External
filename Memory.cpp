#include "Memory.h"

void Memory::PatchEx(HANDLE handle, BYTE* dst, BYTE* src, int size) {
    DWORD protect;
    VirtualProtectEx(handle, dst, size, PAGE_READWRITE, &protect);
    WriteProcessMemory(handle, dst, src, size, nullptr);
    VirtualProtectEx(handle, dst, size, protect, &protect);
}

void Memory::NopEx(HANDLE handle, BYTE* dst, int size) {
    BYTE* nopArray = new BYTE[size];
    memset(nopArray, 0x90, size);

    DWORD protect;

    VirtualProtectEx(handle, dst, size, PAGE_READWRITE, &protect);
    WriteProcessMemory(handle, dst, nopArray, size, nullptr);
    VirtualProtectEx(handle, dst, size, protect, &protect);

    delete[] nopArray;
}
