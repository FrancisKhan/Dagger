cmake_minimum_required (VERSION 3.10)

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

project(DLRCode
    VERSION "1.0"
    DESCRIPTION "DLRCode"
    LANGUAGES CXX)

add_executable(testDLR main.cpp)

ExternalProject_Add(
    DragLibReader 
    PREFIX "DragLibReader-lib"
    #URL https://curl.se/download/curl-7.77.0.tar.gz
    SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/../.
    CMAKE_ARGS
        ${GLOBAL_DEFAULT_ARGS}
        -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/../.
    BUILD_COMMAND make
)

target_include_directories(testDLR PUBLIC ../source)
target_include_directories(testDLR PUBLIC ../external/utilities)
target_include_directories(testDLR PUBLIC ../external/eigen-lib/src/eigen)
target_include_directories(testDLR PUBLIC ../external/spdlog-lib/src/spdlog/include/)
target_include_directories(testDLR PUBLIC ../external/boost-lib/src/boost)
target_include_directories(testDLR PUBLIC ../external/include)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

target_link_libraries(testDLR ${CMAKE_CURRENT_SOURCE_DIR}/../source/libDLR_library.a -lstdc++fs -lcurl -lz)
