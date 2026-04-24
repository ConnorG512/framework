cmake_minimum_required(VERSION 3.28)
project(FilesystemLib CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES  
  src/filesystem.cpp
)

if(WIN32)
  list(APPEND SOURCE_FILES src/system-path-windows.cpp)
elseif(UNIX AND NOT APPLE)
  list(APPEND SOURCE_FILES src/system-path-linux.cpp)
endif()

add_library(lib-filesystem STATIC
  ${SOURCE_FILES}
)

target_include_directories(lib-filesystem PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

install(TARGETS lib-filesystem DESTINATION lib)
install(DIRECTORY include/ DESTINATION include/filesystem)
