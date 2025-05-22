#include <string>
#include <Windows.h>
#include <vector>
#include "../core/logger.h"

class File {
    public:
        File();
        ~File();

        void open(std::string route);
        size_t getSize();
        bool read(std::vector<unsigned char>& data);
        bool write(void* buffer, size_t size);
        void close();
        void createFileMapping();
        char* mapView();
    private:
        std::string file_route;
        char* current_file_map_data;
        HANDLE current_handle;
        HANDLE current_file_map;
        DWORD current_open_type;
};