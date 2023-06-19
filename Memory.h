#ifndef ASSAULTEXTERNAL_MEMORY_H
#define ASSAULTEXTERNAL_MEMORY_H

#include <Windows.h>

namespace Memory {

    void PatchEx(HANDLE handle, BYTE* dst, BYTE* src, int size);
    void NopEx(HANDLE handle, BYTE* dst, int size);
}

#endif //ASSAULTEXTERNAL_MEMORY_H
