cmake_minimum_required(VERSION 3.28)
project(LuaScriptLib CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(LUASCRIPT_IO "Enable the use of lua file io" OFF)
option(LUASCRIPT_OS "Enable the use of lua OS calls" OFF)

set(LUA_SOURCE_FILES 
  "${CMAKE_CURRENT_SOURCE_DIR}/external/lua/lapi.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/lua/lauxlib.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/lua/lbaselib.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/lua/lcode.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/lua/lcorolib.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/lua/lctype.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/lua/ldblib.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/lua/ldebug.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/lua/ldo.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/lua/ldump.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/lua/lfunc.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/lua/lgc.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/lua/linit.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/lua/llex.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/lua/lmathlib.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/lua/lmem.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/lua/loadlib.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/lua/lobject.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/lua/lopcodes.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/lua/lparser.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/lua/lstate.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/lua/lstring.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/lua/lstrlib.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/lua/ltable.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/lua/ltablib.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/lua/ltm.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/lua/lundump.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/lua/lutf8lib.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/lua/lvm.c"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/lua/lzio.c"
)

if(LUASCRIPT_IO)
  list(APPEND LUA_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/external/lua/liolib.c") 
  message(STATUS "LUASCRIPT_IO is enabled")
endif()
if(LUASCRIPT_OS)
  list(APPEND LUA_SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/external/lua/loslib.c") 
  message(STATUS "LUASCRIPT_OS is enabled")
endif()

add_library(luascript-lib STATIC
  src/luascript.cpp
  ${LUA_SOURCE_FILES}
)

target_include_directories(luascript-lib PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
  "${CMAKE_CURRENT_SOURCE_DIR}/external/lua"
)
