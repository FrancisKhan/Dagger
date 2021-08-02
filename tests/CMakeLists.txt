# Tests need to be added as executables first
add_executable(gtest_DLR mathsTests.cpp DLRTests.cpp FileToolsTests.cpp)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

SET(LIB_EXT_DIR ${CMAKE_CURRENT_BINARY_DIR}/../external/lib)

# to link it to the local shared library
add_library(libcurlLocal SHARED IMPORTED GLOBAL)
set_target_properties(
  libcurlLocal
    PROPERTIES 
        IMPORTED_LOCATION ${LIB_EXT_DIR}/libcurl.so
)    

# to link it to the local shared library
add_library(zlibLocal SHARED IMPORTED GLOBAL)
set_target_properties(
  zlibLocal
    PROPERTIES 
        IMPORTED_LOCATION ${LIB_EXT_DIR}/libz.so
)   

target_link_libraries(gtest_DLR PRIVATE DLR_library gtest gtest_main pthread libcurlLocal zlibLocal -lstdc++fs )

# If you register a test, then ctest and make test will run it.
# You can also run examples and check the output, as well.
add_test(NAME gtest_DLR_test COMMAND $<TARGET_FILE:gtest_DLR>) # Command can be a target
