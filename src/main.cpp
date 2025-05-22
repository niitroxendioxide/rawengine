#include <iostream>
#include <Windows.h>
#include <chrono>
#include "./engine/stream/file.h"
#include "./engine/core/inputs.h"
#include "./engine/core/windows.h"
#include "./engine/core/pidhelper.h"
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

void process_sniping() {
    auto pid = PidHelper::findPidByName("troleo.exe");
    if (pid) {
        auto process = PidHelper::openProcessByPid(pid);

        if (process) {
            void *processMemAddress = 0;
            std::cout << "Enter memory address to read: ";
            std::cin >> processMemAddress;

            int processData = 0;
            ReadProcessMemory(process, processMemAddress, &processData, sizeof(processData), nullptr);

            std::cout << "current process data: " << processData << '\n';

            while (true) {
                int newData = 25;
                std::cin >> newData;

                if (newData == 1) {
                    break;
                }

                int success = WriteProcessMemory(process, processMemAddress, &newData, sizeof(newData), nullptr);
                if (!success) {
                    std::cout << "Error writing data" << std::endl;
                }
            }
        }
    }

    std::cout << "Process sniping finished" << std::endl;
}

void snipe_process_from_pid(std::string process_name) {
    auto pid = PidHelper::findPidByName(process_name.c_str());
    if (pid) {
        auto process = PidHelper::openProcessByPid(pid);

        std::cout << "found process!" << std::endl;
        if (process) {
            SYSTEM_INFO SysInfo = MemoryHandler::getSysInfo();

            MEMORY_BASIC_INFORMATION memInfo;
            void *scanAddress = 0;
            std::vector<void*> addresses;

            while (scanAddress < (char*)SysInfo.lpMaximumApplicationAddress) {
                size_t readBytes = VirtualQueryEx(process, scanAddress, &memInfo, sizeof(MEMORY_BASIC_INFORMATION));
                if (!readBytes) {continue;}

                scanAddress = (char*)memInfo.BaseAddress + memInfo.RegionSize;

                if (memInfo.State == MEM_COMMIT && memInfo.Protect == PAGE_READWRITE) {
                    std::vector<char> buffer(memInfo.RegionSize);
                    SIZE_T bytesRead;

                    int value_to_find;
                    std::cout << "Input the value to find:";
                    std::cin >> value_to_find;

                    if (value_to_find == 0) {
                        break;
                    }

                    if (ReadProcessMemory(process, scanAddress, buffer.data(), memInfo.RegionSize, &bytesRead)) {
                        for (size_t i = 0; i < bytesRead - sizeof(int); i += sizeof(int)) {
                            int currentValue;
                            memcpy(&currentValue, &buffer[i], sizeof(int));

                            if (currentValue == value_to_find) {
                                void* foundAddress = (char*)scanAddress + i;
                                addresses.push_back(foundAddress);
                                std::cout << "Found value at address: " << foundAddress << std::endl;
                            }
                        }
                    }
                }
            }

            if (!addresses.empty()) {
                int address_index;
                std::cout << "Select address to modify (0-" << addresses.size()-1 << "): ";
                std::cin >> address_index;

                if (address_index < addresses.size()) {
                    int new_value;
                    std::cout << "New value: ";
                    std::cin >> new_value;

                    size_t bytesWritten;
                    WriteProcessMemory(process, addresses[address_index], &new_value, sizeof(new_value), nullptr);
                } else {
                    std::cout << "Address out of range";
                }
            }
        }
    }
}

int main() {
    //test();
    /*PorkyBoiler pedroilet;
    pedroilet.edad = 18;
    pedroilet.name = "Porky";

    File f;
    f.open("../../hola.bin");

    //f.write(&pedroilet, sizeof(pedroilet));

    std::vector<unsigned char> data;

    if (f.read(data)) {
        PorkyBoiler* recreado = reinterpret_cast<PorkyBoiler*>(data.data());

        std::cout << recreado->name << std::endl;
    }

    //*/
    std::string pidName;

    std::cin >> pidName;

    snipe_process_from_pid(pidName);


    return 0;
}
