#include <iostream>
#include "Process.h"
#include "Memory.h"

int main() {
    DWORD processId = Process::GetProcessId("ac_client.exe");
    uintptr_t moduleBase;

    while (processId == -1) {
        std::cout << "Finding to ac_client.exe..." << std::endl;
        processId = Process::GetProcessId("ac_client.exe");
        Sleep(1000);
    }

    moduleBase = Process::GetModuleBaseAddress(processId, "ac_client.exe");

    std::cout << "ac_client.exe is founded!" << std::endl;
    std::cout << "ProcessID: " << processId << std::endl;
    std::cout << "ModuleBaseAddress: 0x" << std::hex << moduleBase << std::endl;

    Sleep(3000);

    HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, 0, processId);
    bool infHealth, infArmor, infHealthP, infArmorP;
    infHealth = infArmor = infHealthP = infArmorP = false;

    std::cout << "Infinite Health (F1)" << std::endl;
    std::cout << "Infinite Armor (F2)" << std::endl;
    std::cout << "Infinite Health Patch (F3)" << std::endl;
    std::cout << "Infinite Armor Patch (F4)" << std::endl;

    while (Process::GetProcessId("ac_client.exe") != -1) {
        if (GetAsyncKeyState(VK_F1) & 1) {
            infHealth = !infHealth;
            std::cout << "Infinite Health: " << std::boolalpha << infHealth << std::endl;
        }

        if (GetAsyncKeyState(VK_F2) & 1) {
            infArmor = !infArmor;
            std::cout << "Infinite Armor: " << std::boolalpha << infArmor << std::endl;
        }

        if (GetAsyncKeyState(VK_F3) & 1) {
            infHealthP = !infHealthP;
            std::cout << "Infinite Health Patch: " << std::boolalpha << infHealthP << std::endl;

            BYTE* address = (BYTE*) (moduleBase + 0x29D1F);
            if (infHealthP) {
                Memory::NopEx(handle, address, 3);
            } else {
                Memory::PatchEx(handle, address, (BYTE*) "\x29\x7B\x04", 3);
            }
        }

        if (GetAsyncKeyState(VK_F4) & 1) {
            infArmorP = !infArmorP;
            std::cout << "Infinite Armor: " << std::boolalpha << infArmorP << std::endl;

            BYTE* address = (BYTE*) (moduleBase + 0x29D0B);
            if (infArmorP) {
                Memory::NopEx(handle, address, 3);
            } else {
                Memory::PatchEx(handle, address, (BYTE*) "\x89\x73\x08", 3);
            }
        }

        uintptr_t localPlayer = (uintptr_t) moduleBase + 0x10F4F4;

        if (localPlayer) {
            int value = 1337;

            if (infHealth) {
                WriteProcessMemory(handle, (BYTE*) (localPlayer + 0xF8), &value, sizeof(value), nullptr);
            }

            if (infArmor) {
                WriteProcessMemory(handle, (BYTE*) (localPlayer + 0xFC), &value, sizeof(value), nullptr);
            }
        }

        Sleep(10);
    }

    return 0;
}