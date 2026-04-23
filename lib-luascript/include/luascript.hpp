#pragma once

#include "types.hpp"

#include <cassert>
#include <expected>
#include <filesystem>
#include <memory>
#include <span>
#include <string>

extern "C"
{
#include "lauxlib.h"
#include "lua.h"
}

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

enum class LuaPullValErr
{
  TABLE_PATH_EMPTY,
  NO_VALID_RETURN_VALUE,
  RECIEVED_STRING_IS_NULL,
  GLOBAL_DOES_NOT_EXIST,
};

[[nodiscard]] std::expected<void, LuaCPushErr> register_function_list(Inst &lua_instance,
                                                                      const std::span<const lua_CFunction> func_list);
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
}; // namespace FW::LScript

// Implementation files:
#include "luascript.ipp"


namespace FW::LScript {
  [[nodiscard]] bool execute_file_list(Inst &instance, const std::span<const std::filesystem::path> file_list) noexcept;
}
