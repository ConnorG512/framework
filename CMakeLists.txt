cmake_minimum_required(VERSION 3.28)
project(FrameworkCore CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Toggle libraries: 
option(USE_FILESYSTEM_LIB "Include filesystem library" ON)
option(USE_LOGGER_LIB "Include logger library" ON)

add_compile_options(
  -Wall
  -Wextra
  -Wpedantic
)

# Activate flags.
if(USE_FILESYSTEM_LIB)
  add_subdirectory(lib-filesystem)
endif()
if(USE_LOGGER_LIB)
  add_subdirectory(lib-logger)
endif()
