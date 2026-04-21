#include "lauxlib.h"
#include "lua.h"
#include "luascript.hpp"
#include <cassert>

std::expected<void, FW::LScript::LuaCPushErr> FW::LScript::Inst::register_function(const lua_CFunction func) noexcept
{
  assert(func != nullptr && "lua function passed cannot be nullptr!");
  if (func == nullptr)
    return std::unexpected(FW::LScript::LuaCPushErr::FUNC_IS_NULLPTR);
  lua_pushcfunction(lua_.get(), func);

  return {};
}

std::expected<void, FW::LScript::LuaCPushErr>
FW::LScript::register_function_list(Inst &lua_instance, const std::span<const lua_CFunction> func_list)
{
  assert(!func_list.empty() && "Function list should not be empty!");
  if (func_list.empty())
    return std::unexpected(FW::LScript::LuaCPushErr::LIST_EMPTY);
  else
  {
    for (const auto c_func : func_list)
      if (const auto reg_status = lua_instance.register_function(c_func); !reg_status.has_value())
        return std::unexpected(reg_status.error());

    return {};
  }
}

[[nodiscard]] bool FW::LScript::Inst::execute_file(const std::filesystem::path &path_to_file) noexcept 
{
  if(luaL_dofile(lua_.get(), path_to_file.c_str()) != LUA_OK)
    return false;
  else 
    return true;
}

[[nodiscard]] bool FW::LScript::execute_file_list(Inst &instance, const std::span<const std::filesystem::path> file_list) noexcept
{
  assert(!file_list.empty());

  for (const auto& file : file_list)
  {
    if(!instance.execute_file(file))
      return false;
  }
  return true;
}
