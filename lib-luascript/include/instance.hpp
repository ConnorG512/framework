#pragma once

#include "concepts.hpp"
#include "errors.hpp"

#include <expected>
#include <filesystem>

extern "C"
{
#include "lauxlib.h"
#include "lua.h"
}

namespace FW::LS
{

class Inst
{
public:
  Inst() = default;
  [[nodiscard]] std::expected<void, LuaCPushErr> register_function(lua_CFunction func) noexcept;

  template <LuaType LuaValue>
  [[nodiscard]] std::expected<LuaValue, LuaPullValErr> get_value_from_script(const std::string &table_path);
  [[nodiscard]] bool execute_file(const std::filesystem::path &path_to_file) noexcept;

private:
  std::unique_ptr<lua_State, decltype(&lua_close)> lua_{luaL_newstate(), &lua_close};
};


}; // namespace FW::LS

#include "instance.ipp"
