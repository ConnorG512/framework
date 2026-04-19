cmake_minimum_required(VERSION 3.28)
project(FilesystemLib CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES  
  src/filesystem.cpp
)

if(WIN32)
  list(APPEND SOURCE_FILES src/system-path-windows.cpp)
elseif(LINUX)
  list(APPEND SOURCE_FILES src/system-path-linux.cpp)
endif()

add_library(filesystem-lib STATIC
  ${SOURCE_FILES}
)

target_include_directories(filesystem-lib PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
