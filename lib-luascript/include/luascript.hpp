#pragma once

#include <expected>
#include <span>
extern "C"
{
#include "lauxlib.h"
#include "lua.h"
}

#include <memory>

// Forward
namespace FW
{
namespace LScript
{
class Inst;
}
} // namespace FW
//

namespace FW::LScript
{
enum class LuaCPushErr
{
  FUNC_IS_NULLPTR,
  LIST_EMPTY,
};

[[nodiscard]] std::expected<void, LuaCPushErr> register_function_list(Inst &lua_instance,
                                                                      const std::span<const lua_CFunction> func_list);

class Inst
{
public:
  Inst() = default;

  [[nodiscard]] std::expected<void, LuaCPushErr> register_function(lua_CFunction func) noexcept;

private:
  std::unique_ptr<lua_State, decltype(&lua_close)> lua_{luaL_newstate(), &lua_close};
};
}; // namespace FW::LScript
