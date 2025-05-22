#include "./file.h"

File::File() {}
File::~File() {}

void File::open(std::string route) {
    // add functionality brah
    current_handle = CreateFileA(route.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (current_handle == INVALID_HANDLE_VALUE) {
        Logger::logError(Logger::getLastError());

        return;
    }
}

bool File::read(std::vector<unsigned char>& data) {
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
    LARGE_INTEGER fileSize;
    if (!GetFileSizeEx(current_handle, &fileSize)) {
        Logger::logError(Logger::getLastError());
        close();

        return 0;
    }

    return fileSize.QuadPart;
}

void File::close() {
    if (current_handle) {
        CloseHandle(current_handle);
    }
}