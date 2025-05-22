#include "pidhelper.h"

DWORD PidHelper::findPidByName(const char* pid_name) {
    HANDLE pid_handle;
    PROCESSENTRY32 process;

    // first parameter gets all processes, second is not needfed in this case
    pid_handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    process.dwSize = sizeof(PROCESSENTRY32);

    do {
        if (strcmp((char*)process.szExeFile, pid_name) == 0) {
            DWORD pid = process.th32ProcessID;
            CloseHandle(pid_handle);

            return pid;
        }
    } while (Process32Next(pid_handle, &process));

    CloseHandle(pid_handle);
}



HANDLE PidHelper::openProcessByPid(DWORD pid) {
    return OpenProcess(PROCESS_ALL_ACCESS, 0, pid);
}