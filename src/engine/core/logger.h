#include <iostream>
#include <Windows.h>
#include <string>

namespace Logger {

    static void resetCursor() {
        HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);

        SetConsoleCursorPosition(stdHandle, {0, 0});
    }

    static std::string getLastError() {
        DWORD error = GetLastError();

        if (!error) { return ""; }

        char *message = 0;
        size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            0,error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char *) &message, 0, nullptr);

        std::string rez(message, size);

        LocalFree(message);

        return rez;
    }

    template<typename T>
    static void logError(T msg) {
        HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);

        SetConsoleTextAttribute(stdHandle, 0x0C);
        std::cout << "[ERROR]: " << msg << std::endl;

        SetConsoleTextAttribute(stdHandle, 0x0F);
    };

    template<typename T>
    static void logMessage(T msg) {
        HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);

        std::cout << "[SYSTEM]: " << msg << std::endl;
    }
};