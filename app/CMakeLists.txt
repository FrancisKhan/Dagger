add_executable(almost main.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

IF (WIN32)
  SET(CMAKE_EXE_LINKER_FLAGS "-static")
ENDIF()

target_link_libraries(almost PRIVATE backbone_library)
