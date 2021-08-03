cmake_minimum_required (VERSION 3.10)

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

ExternalProject_Add(
    eigen 
    PREFIX "eigen-lib"
    URL https://gitlab.com/libeigen/eigen/-/archive/master/eigen-master.tar.gz
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)

ExternalProject_Add(
    spdlog 
    PREFIX "spdlog-lib"
    URL https://codeload.github.com/gabime/spdlog/zip/v1.8.5
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)

ExternalProject_Add(
    libcurl 
    PREFIX "libcurl-lib"
    URL https://curl.se/download/curl-7.77.0.tar.gz
    SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/libcurl-lib/src/libcurl
    CMAKE_ARGS
        ${GLOBAL_DEFAULT_ARGS}
        -DCMAKE_INSTALL_PREFIX=${CMAKE_SOURCE_DIR}/external
    BUILD_COMMAND make
)

# to link to the local shared library
add_library(libcurlLocal SHARED IMPORTED GLOBAL)
set_target_properties(
  libcurlLocal
    PROPERTIES 
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/libcurl.so
)    

ExternalProject_Add(
    boost 
    PREFIX "boost-lib"
    URL https://boostorg.jfrog.io/artifactory/main/release/1.76.0/source/boost_1_76_0.tar.gz
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)

ExternalProject_Add(
    zlib 
    PREFIX "zlib-lib"
    URL https://zlib.net/zlib-1.2.11.tar.gz
    SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/zlib-lib/src/zlib
    CMAKE_ARGS
        ${GLOBAL_DEFAULT_ARGS}
        -DCMAKE_INSTALL_PREFIX=${CMAKE_SOURCE_DIR}/external
    BUILD_COMMAND make
)

# to link to the local shared library
add_library(zlibLocal SHARED IMPORTED GLOBAL)
set_target_properties(
  zlibLocal
    PROPERTIES 
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/libz.so
)   

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()