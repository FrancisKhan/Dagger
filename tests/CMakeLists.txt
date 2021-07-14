# Tests need to be added as executables first
add_executable(gtest_DLR mathsTests.cpp DLRTests.cpp FileToolsTests.cpp)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

IF (WIN32)
  SET(CMAKE_EXE_LINKER_FLAGS "-static")
ENDIF()

target_link_libraries(gtest_DLR PRIVATE DLR_library gtest gtest_main pthread)

# If you register a test, then ctest and make test will run it.
# You can also run examples and check the output, as well.
add_test(NAME gtest_DLR_test COMMAND $<TARGET_FILE:gtest_DLR>) # Command can be a target
