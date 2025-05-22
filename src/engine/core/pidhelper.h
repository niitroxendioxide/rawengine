#include <Windows.h>
#include <tlhelp32.h>

struct PidHelper {

    static DWORD findPidByName(const char* pid_name);

    static HANDLE openProcessByPid(DWORD pid);
};