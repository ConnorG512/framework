cmake_minimum_required(VERSION 3.28)
project(LuaScriptLib CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(luascript-lib STATIC
  src/luascript.cpp
)

target_include_directories(luascript-lib PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
