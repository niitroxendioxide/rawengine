#include "./file.h"

File::File() {}
File::~File() {}

void File::open(std::string route) {
    if (current_handle && current_open_type != OPEN_EXISTING) {
        close();
    }

    // add functionality brah
    file_route = route;
    current_handle = CreateFileA(file_route.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    current_open_type = OPEN_EXISTING;

    if (current_handle == INVALID_HANDLE_VALUE) {
        Logger::logError("File::open() - " + Logger::getLastError());

        return;
    }
}

bool File::read(std::vector<unsigned char>& data) {
    if (current_handle == NULL || current_open_type == CREATE_ALWAYS) {
        open(file_route);
    }

    // clear the vector for obvious reasons
    data.clear();

    size_t fileSize = getSize();
    DWORD totalBytesRead = 0;

    data.resize(fileSize);

    bool readstatus = ReadFile(current_handle, data.data(), fileSize, &totalBytesRead, nullptr);

    if (!readstatus || totalBytesRead != fileSize) {
        return false;
    }

    return true;
}

bool File::write(void* buffer, size_t size) {
    if (current_handle != NULL && current_open_type != CREATE_ALWAYS) {
        close();
    }

    current_handle = CreateFileA(file_route.c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (current_handle == INVALID_HANDLE_VALUE) {
        Logger::logError("File::write() - " + Logger::getLastError());

        return false;
    }

    current_open_type = CREATE_ALWAYS;

    size_t fileSize = getSize();

    DWORD totalBytesWritten = 0;
    bool success = WriteFile(current_handle, buffer, size, &totalBytesWritten, NULL);

    if (totalBytesWritten != size) {
        success = false;
    }

    close();

    return success;
}

size_t File::getSize() {
    if (current_handle == NULL) {
        return 0;
    }

    LARGE_INTEGER fileSize;
    if (!GetFileSizeEx(current_handle, &fileSize)) {
        Logger::logError("File::fileSize() - " + Logger::getLastError());
        close();

        return 0;
    }

    return fileSize.QuadPart;
}

void File::createFileMapping() {
    close();

    current_handle = CreateFileA(file_route.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (current_handle == INVALID_HANDLE_VALUE) {
        Logger::logError("File::createFileMapping()" + Logger::getLastError());
        return;
    }

    constexpr int size = 100;
    current_file_map = CreateFileMappingA(current_handle, NULL, PAGE_READWRITE, 0, size, NULL);
    if (!current_file_map) {
        close();
    }
}

char* File::mapView() {
    constexpr int fileMapSize = 100;

    createFileMapping();

    char* data = (char*)MapViewOfFile(current_file_map, FILE_MAP_ALL_ACCESS, 0, 0, fileMapSize);
    current_file_map_data = data;

    return data;
}

void File::close() {
    if (current_file_map) {
        UnmapViewOfFile(current_file_map_data);
        CloseHandle(current_file_map);
    }

    if (current_handle) {
        CloseHandle(current_handle);
        current_handle = NULL;
    }
}