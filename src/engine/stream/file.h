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

    private:
        // none for now?
        HANDLE current_handle;
};