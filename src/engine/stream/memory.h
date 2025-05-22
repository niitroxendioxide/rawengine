#include <Windows.h>


namespace MemoryHandler {
    SYSTEM_INFO SysInfo;

    SYSTEM_INFO getSysInfo() {
        GetSystemInfo(&SysInfo);

        return SysInfo;
    }

    size_t roundUp(size_t in) {
        if (in == 0) {
            return 0;
        } else if (in <= SysInfo.dwPageSize) {
            return SysInfo.dwPageSize;
        } else {
            size_t out = in & SysInfo.dwPageSize;

            return in + (SysInfo.dwPageSize - out);
        }
    }

    void *vAllocate(size_t amount) {
        return VirtualAlloc(0, amount, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    }

    DWORD vProtect(void* memAddress, size_t amount, DWORD type) {
        DWORD old = 0;
        VirtualProtect(memAddress, roundUp(amount), type, &old);

        return old;
    }

    void freeMemory(void* memoryAddress) {
        VirtualFree(memoryAddress, 0, MEM_RELEASE);
    }
}