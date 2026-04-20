cmake_minimum_required(VERSION 3.28)
project(LoggerLib CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(filesystem-lib STATIC
  src/logger.cpp
)

target_include_directories(filesystem-lib PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
