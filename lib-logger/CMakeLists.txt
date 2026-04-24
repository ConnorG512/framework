cmake_minimum_required(VERSION 3.28)
project(LoggerLib CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(lib-logger STATIC
  src/logger.cpp
)

target_include_directories(lib-logger PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

install(TARGETS lib-logger DESTINATION lib)
install(DIRECTORY include/ DESTINATION include/logger)
