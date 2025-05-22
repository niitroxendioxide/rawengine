#include <iostream>
#include <Windows.h>
#include <chrono>
#include "./engine/stream/file.h"
#include "./engine/core/inputs.h"
#include "./engine/core/windows.h"
#include "./engine/stream/memory.h"

std::string DEFAULT_IN_OUT_ROUTE = "../../hola.txt";

void test() {
    bool program_active = true;
    int posx = 0;
    int posy = 0;

    std::system("cls");

    auto start = std::chrono::high_resolution_clock::now();
    while(program_active) {
        auto current = std::chrono::high_resolution_clock::now();
        float dt = (std::chrono::duration_cast<std::chrono::microseconds>(current - start)).count();
        start = current;

        static float counter = 1000.0f;
        counter -= dt;

        if (counter <= 0) {

            counter += 1000.0;

            if (InputHandler::is_input_down('A')) {
                posx -= 1;
            } else if (InputHandler::is_input_down('D')) {
                posx += 1;
            } else if (InputHandler::is_input_down('S')) {
                posy += 1;
            } else if (InputHandler::is_input_down('W')) {
                posy -= 1;
            }

            if (posx > 4) posx = 0;
            if (posx < 0) posx = 4;
            if (posy > 4) posy = 0;
            if (posy < 0) posy = 4;

            Logger::resetCursor();

            for (int y = 0; y < 5; y++) {
                for (int x = 0; x < 5; x++) {
                    std::cout << (posx == x && posy == y ? "[X]" : "[ ]");
                }

                std::cout << std::endl;
            }
        }
    }
}

struct testData {
    int a;
    float b;
};

int main() {
    //test();
    MemoryHandler::getSysInfo();
    void *allocatedMemory = MemoryHandler::vAllocate(250);
    if (allocatedMemory) {
        std::cout << "Memory:" << allocatedMemory << std::endl;

        ((unsigned char*)allocatedMemory)[5] = 128;

        std::cout << (int)((unsigned char*)allocatedMemory)[5] << "\n";

        MemoryHandler::freeMemory(allocatedMemory);
    }

    return 0;
}
