cmake_minimum_required (VERSION 3.10)

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

project(DLRCode
    VERSION "1.0"
    DESCRIPTION "DLRCode"
    LANGUAGES CXX)

add_executable(DaggerCode Solver.cpp Material.cpp main.cpp)

ExternalProject_Add(
    dragLibReader 
    PREFIX "dragLibReader-lib"
    URL https://github.com/FrancisKhan/DragLibReader/archive/refs/heads/master.zip
    BUILD_IN_SOURCE ON
)

SET(LIB_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR}/dragLibReader-lib/src/dragLibReader)

target_include_directories(DaggerCode PUBLIC ${LIB_SRC_DIR}/source)
target_include_directories(DaggerCode PUBLIC ${LIB_SRC_DIR}/external/utilities)
target_include_directories(DaggerCode PUBLIC ${LIB_SRC_DIR}/external/eigen-lib/src/eigen)
target_include_directories(DaggerCode PUBLIC ${LIB_SRC_DIR}/external/spdlog-lib/src/spdlog/include/)
target_include_directories(DaggerCode PUBLIC ${LIB_SRC_DIR}/external/boost-lib/src/boost)
target_include_directories(DaggerCode PUBLIC ${LIB_SRC_DIR}/external/include)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# to link it to the local shared library
add_library(libcurlLocal SHARED IMPORTED)
set_target_properties(
  libcurlLocal
    PROPERTIES 
        IMPORTED_LOCATION ${LIB_SRC_DIR}/external/lib/libcurl.so
)    

# to link it to the local shared library
add_library(zlibLocal SHARED IMPORTED)
set_target_properties(
  zlibLocal
    PROPERTIES 
        IMPORTED_LOCATION ${LIB_SRC_DIR}/external/lib/libz.so
)   

target_link_libraries(DaggerCode ${LIB_SRC_DIR}/source/libDagger_library.a libcurlLocal zlibLocal -lstdc++fs)
