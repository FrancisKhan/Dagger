# Tests need to be added as executables first
add_executable(gtest_Dagger mathsTests.cpp XSTests.cpp XSMatrixTests.cpp FileToolsTests.cpp
               InterpolationTests.cpp)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

target_link_libraries(gtest_Dagger PRIVATE Dagger_library gtest gtest_main pthread libcurlLocal zlibLocal -lstdc++fs)

# If you register a test, then ctest and make test will run it.
# You can also run examples and check the output, as well.
add_test(NAME gtest_Dagger_test COMMAND $<TARGET_FILE:gtest_Dagger>) # Command can be a target
