cmake_minimum_required(VERSION 3.28)
project(FrameworkCore CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Toggle libraries: 
option(USE_FILESYSTEM_LIB "Include filesystem library" ON)

add_compile_options(
  -Wall
  -Wextra
  -Wpedantic
)

if(USE_FILESYSTEM)
  add_subdirectory(lib-filesystem)
endif()
