cmake_minimum_required(VERSION 3.28)
project(LuaScriptLib CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(LUASCRIPT_IO "Enable the use of lua file io" OFF)
option(LUASCRIPT_OS "Enable the use of lua OS calls" OFF)

set(LUA_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/lua")

set(LUA_SOURCE_FILES 
  "${LUA_SRC_DIR}/lapi.c"
  "${LUA_SRC_DIR}/lauxlib.c"
  "${LUA_SRC_DIR}/lbaselib.c"
  "${LUA_SRC_DIR}/lcode.c"
  "${LUA_SRC_DIR}/lcorolib.c"
  "${LUA_SRC_DIR}/lctype.c"
  "${LUA_SRC_DIR}/ldblib.c"
  "${LUA_SRC_DIR}/ldebug.c"
  "${LUA_SRC_DIR}/ldo.c"
  "${LUA_SRC_DIR}/ldump.c"
  "${LUA_SRC_DIR}/lfunc.c"
  "${LUA_SRC_DIR}/lgc.c"
  "${LUA_SRC_DIR}/linit.c"
  "${LUA_SRC_DIR}/llex.c"
  "${LUA_SRC_DIR}/lmathlib.c"
  "${LUA_SRC_DIR}/lmem.c"
  "${LUA_SRC_DIR}/loadlib.c"
  "${LUA_SRC_DIR}/lobject.c"
  "${LUA_SRC_DIR}/lopcodes.c"
  "${LUA_SRC_DIR}/lparser.c"
  "${LUA_SRC_DIR}/lstate.c"
  "${LUA_SRC_DIR}/lstring.c"
  "${LUA_SRC_DIR}/lstrlib.c"
  "${LUA_SRC_DIR}/ltable.c"
  "${LUA_SRC_DIR}/ltablib.c"
  "${LUA_SRC_DIR}/ltm.c"
  "${LUA_SRC_DIR}/lundump.c"
  "${LUA_SRC_DIR}/lutf8lib.c"
  "${LUA_SRC_DIR}/lvm.c"
  "${LUA_SRC_DIR}/lzio.c"
)

if(NOT EXISTS "${LUA_SRC_DIR}")
  message(FATAL_ERROR "Lua source directory missing, ensure that the submodule as been pulled!")
endif()

if(LUASCRIPT_IO)
  list(APPEND LUA_SOURCE_FILES "${LUA_SRC_DIR}/liolib.c") 
  message(STATUS "LUASCRIPT_IO is enabled")
endif()
if(LUASCRIPT_OS)
  list(APPEND LUA_SOURCE_FILES "${LUA_SRC_DIR}/loslib.c") 
  message(STATUS "LUASCRIPT_OS is enabled")
endif()

add_library(lib-luascript STATIC
  src/files.cpp
  src/function.cpp
  src/instance.cpp
  ${LUA_SOURCE_FILES}
)

target_include_directories(lib-luascript 
  PRIVATE
  ${LUA_SRC_DIR}

  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/luascript>
)

install(DIRECTORY include/ DESTINATION include/luascript)
install(TARGETS lib-luascript DESTINATION lib)
