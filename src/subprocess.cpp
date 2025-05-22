#include <iostream>
#include "./engine/core/inputs.h"

int main() {
    SYSTEM_INFO SysInfo;

    GetSystemInfo(&SysInfo);
    int data = 10;

    std::cout << &data << std::endl;

    while(true) {
        if (GetAsyncKeyState('C') & 0b1) {
            std::cout << data << std::endl;
        } else if (GetAsyncKeyState('B') & 0b1) {
            std::cout << &data << std::endl;
        }
    }

    std::cin.get();

    return 0;
}