#include <iostream>
#include "./windows.h"


void WinHandler::showScreenMessage(std::string message, UINT type) {
    int status = MessageBoxA(0, message.c_str(), "System Message", type);
    if (status == IDOK) {
        std::cout << "User clicked ok" << std::endl;
    } else {
        std::cout << "Failure" << std::endl;
    }
};

void WinHandler::createWindow() {
    
}