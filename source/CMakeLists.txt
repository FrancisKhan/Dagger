cmake_minimum_required (VERSION 3.10)

# Make an automatic library - will be static or dynamic based on user setting
add_library(DLR_library Output.cpp Library.cpp NuclideBlock.cpp
			Nuclide.cpp CrossSection.cpp CrossSectionSet.cpp
			CrossSectionMatrix.cpp CrossSectionMatrixSet.cpp
			../external/utilities/additionalPrintFuncs.cpp 
			../external/utilities/inputParser.cpp
			../external/utilities/network_tools.cpp 
			../external/utilities/gzip.cpp 
			../external/utilities/zlib.cpp)

target_include_directories(DLR_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/.)
target_include_directories(DLR_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../external/utilities)
target_include_directories(DLR_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../external/eigen-lib/src/eigen)
target_include_directories(DLR_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../external/spdlog-lib/src/spdlog/include/)
target_include_directories(DLR_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../external/boost-lib/src/boost)
target_include_directories(DLR_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../external/include)

SET(LIB_EXT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../external/lib)

# to link it to the local shared library
add_library(libcurlLocal SHARED IMPORTED)
set_target_properties(
  libcurlLocal
    PROPERTIES 
        IMPORTED_LOCATION ${LIB_EXT_DIR}/libcurl.so
)    

# to link it to the local shared library
add_library(zlibLocal SHARED IMPORTED)
set_target_properties(
  zlibLocal
    PROPERTIES 
        IMPORTED_LOCATION ${LIB_EXT_DIR}/libz.so
)   

# Experimental/filesystem C++ library
target_link_libraries(DLR_library libcurlLocal zlibLocal -lstdc++fs)

# All users of this library will need at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

target_compile_options(DLR_library PUBLIC -Wall)
