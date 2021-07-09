cmake_minimum_required (VERSION 3.10)

# Make an automatic library - will be static or dynamic based on user setting
add_library(backbone_library IO/Output.cpp Datamodel/KineticsSet.cpp
			Datamodel/Reactor.cpp Reader/Library.cpp Reader/NuclideBlock.cpp
			Datamodel/Nuclide.cpp Datamodel/CrossSection.cpp Datamodel/CrossSectionSet.cpp
			Datamodel/CrossSectionMatrix.cpp Datamodel/CrossSectionMatrixSet.cpp
			Utilities/additionalPrintFuncs.cpp Utilities/inputParser.cpp)

# We need this directory, and users of our library will need it too
target_include_directories(backbone_library PUBLIC Datamodel)
target_include_directories(backbone_library PUBLIC IO)
target_include_directories(backbone_library PUBLIC Reader)
target_include_directories(backbone_library PUBLIC Utilities)
target_include_directories(backbone_library PUBLIC ../External/eigen-lib/src/eigen)
target_include_directories(backbone_library PUBLIC ../External/spdlog-lib/src/spdlog/include/)

# Experimental/filesystem C++ library
target_link_libraries(backbone_library -lstdc++fs)

# All users of this library will need at least C++17

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#target_compile_features(cpm_library PUBLIC cxx_std_17)
target_compile_options(backbone_library PUBLIC -Wall -Wno-ignored-attributes)
