cmake_minimum_required (VERSION 3.10)

# Make an automatic library - will be static or dynamic based on user setting
add_library(DLR_library IO/Output.cpp reader/Library.cpp reader/NuclideBlock.cpp
			datamodel/Nuclide.cpp datamodel/CrossSection.cpp datamodel/CrossSectionSet.cpp
			datamodel/CrossSectionMatrix.cpp datamodel/CrossSectionMatrixSet.cpp
			utilities/additionalPrintFuncs.cpp utilities/inputParser.cpp
			utilities/network_tools.cpp utilities/gzip.cpp utilities/zlib.cpp)

# We need this directory, and users of the library will need it too
target_include_directories(DLR_library PUBLIC datamodel)
target_include_directories(DLR_library PUBLIC IO)
target_include_directories(DLR_library PUBLIC reader)
target_include_directories(DLR_library PUBLIC utilities)
target_include_directories(DLR_library PUBLIC ../external/eigen-lib/src/eigen)
target_include_directories(DLR_library PUBLIC ../external/spdlog-lib/src/spdlog/include/)
target_include_directories(DLR_library PUBLIC ../external/boost-lib/src/boost)
target_include_directories(DLR_library PUBLIC ../external/include)

link_directories(../external/lib)

# Experimental/filesystem C++ library
target_link_libraries(DLR_library -lstdc++fs -lcurl -lz)

# All users of this library will need at least C++17

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

target_compile_options(DLR_library PUBLIC -Wall -Wno-ignored-attributes)
