cmake_minimum_required (VERSION 3.10)

project(DragLibReader
    VERSION 1.0
    DESCRIPTION "DragLibReader"
    LANGUAGES CXX)
	
# Let's ensure -std=c++xx instead of -std=g++xx
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-Wall")

include(CTest)

# External library directory
add_subdirectory(external)

# Backbone directory
add_subdirectory(source)

# Tests are here
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING) AND BUILD_TESTING)
    add_subdirectory(tests)
endif()