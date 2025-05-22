#include <iostream>
#include "./windows.h"

void WinHandler::show_screen_message(const char* message) {
    int status = MessageBoxA(0, message, "System Message", MB_OK);
    if (status == IDOK) {
        std::cout << "User clicked ok" << std::endl;
    } else {
        std::cout << "Failure" << std::endl;
    }
};

void WinHandler::create_window() {
    
}