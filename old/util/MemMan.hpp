#pragma once
#pragma warning (disable : 6001 )
#pragma warning (disable : 4244 )

#define WIN32_LEAN_AND_MEAN 

#include <Windows.h>
#include <TlHelp32.h>
#include <tchar.h>


class MemoryManagement {
public:
    HANDLE proc;

    struct moduleData {
        HMODULE module;
        DWORD_PTR base;
        uintptr_t size;
    };


    template <class T>
    T ReadMem(uintptr_t addr)
    {
        T x;
        ReadProcessMemory(proc, (LPBYTE*)addr, &x, sizeof(x), NULL);
        return x;
    }

    bool ReadRawMem(uintptr_t addr, void* buffer, size_t size)
    {
        SIZE_T bytesRead;
        if (ReadProcessMemory(proc, reinterpret_cast<LPCVOID>(addr), buffer, size, &bytesRead))
        {
            return bytesRead == size;
        }
        return false;
    }


    template <class T>
    T WriteMem(uintptr_t addr, T x)
    {
        WriteProcessMemory(proc, (LPBYTE*)addr, &x, sizeof(x), NULL);
        return x;
    }


    HANDLE getProcess(const wchar_t* name) {
        HANDLE processID = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        uintptr_t process;
        PROCESSENTRY32W processEntry;
        processEntry.dwSize = sizeof(processEntry);

        do {
            if (!_wcsicmp(processEntry.szExeFile, name)) {
                process = processEntry.th32ProcessID;
                CloseHandle(processID);
                proc = OpenProcess(PROCESS_ALL_ACCESS, false, process);
            }
        } while (Process32NextW(processID, &processEntry));

        return proc;
    };


    uintptr_t getPid(const wchar_t* name) {
        HANDLE processID = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        uintptr_t process;
        PROCESSENTRY32W processEntry;
        processEntry.dwSize = sizeof(processEntry);

        do {
            if (!_wcsicmp(processEntry.szExeFile, name)) {
                process = processEntry.th32ProcessID;
                CloseHandle(processID);
                proc = OpenProcess(PROCESS_ALL_ACCESS, false, process);
            }
        } while (Process32NextW(processID, &processEntry));

        return process;
    }


    HMODULE getModule(uintptr_t pid, const wchar_t* name) {
        HANDLE module = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
        MODULEENTRY32W moduleEntry;
        moduleEntry.dwSize = sizeof(moduleEntry);

        do {
            if (!_wcsicmp(moduleEntry.szModule, name)) {
                CloseHandle(module);
                return moduleEntry.hModule;
            }
        } while (Module32NextW(module, &moduleEntry));

        return 0;
    }


    DWORD_PTR getModuleBase(DWORD pid, LPCTSTR name) {
        DWORD_PTR dwBase = 0;
        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
        MODULEENTRY32 ModuleEntry32;
        ModuleEntry32.dwSize = sizeof(MODULEENTRY32);

        if (Module32First(hSnapshot, &ModuleEntry32)) {
            do {
                if (_tcsicmp(ModuleEntry32.szModule, name) == 0) {
                    dwBase = (DWORD_PTR)ModuleEntry32.modBaseAddr;
                }
            } while (Module32Next(hSnapshot, &ModuleEntry32));
        };

        return dwBase;
    }


    DWORD getModuleSize(DWORD pid, LPCTSTR name) {
        DWORD dwSize = 0;

        do {
            HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
            if (hSnapshot == INVALID_HANDLE_VALUE) { continue; }

            MODULEENTRY32 ModuleEntry32;
            ModuleEntry32.dwSize = sizeof(MODULEENTRY32);

            if (Module32First(hSnapshot, &ModuleEntry32)) {
                do {
                    if (_tcsicmp(ModuleEntry32.szModule, name) == 0) {
                        dwSize = ModuleEntry32.modBaseSize;
                        break;
                    }
                } while (Module32Next(hSnapshot, &ModuleEntry32));
            }

            CloseHandle(hSnapshot);
        } while (!dwSize);

        return dwSize;
    }
};