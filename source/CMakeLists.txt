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

target_include_directories(DLR_library PUBLIC .)
target_include_directories(DLR_library PUBLIC ../external/utilities)
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

target_compile_options(DLR_library PUBLIC -Wall)
