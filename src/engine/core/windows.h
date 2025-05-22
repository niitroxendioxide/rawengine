#include <Windows.h>

struct WinHandler {

    static void showScreenMessage(std::string message, UINT type);
    static void createWindow();
};