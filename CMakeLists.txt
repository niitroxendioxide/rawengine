cmake_minimum_required(VERSION 3.15)
project(CustomGameEngine VERSION 0.1.0 LANGUAGES C CXX)
set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/project)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)



include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine
)


file(GLOB CORE_SOURCES src/engine/core/*.cpp)
file(GLOB RENDER_SOURCES src/engine/render/*.cpp)
file(GLOB STREAM_SOURCES src/engine/stream/*.cpp)
file(GLOB MAIN_SOURCE src/main.cpp)

add_executable(${PROJECT_NAME} ${WIN32_FLAG}
    ${MAIN_SOURCE}
    ${CORE_SOURCES}
    ${RENDER_SOURCES}
    ${STREAM_SOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    kernel32.lib
    user32.lib
    gdi32.lib
    winspool.lib
    shell32.lib
    ole32.lib
    oleaut32.lib
    uuid.lib
    comdlg32.lib
    advapi32.lib
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})