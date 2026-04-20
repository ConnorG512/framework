#include "lua.h"
#include "luascript.hpp"
#include <cassert>

namespace
{

}

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
