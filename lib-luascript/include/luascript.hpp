#pragma once

#include "types.hpp"

#include <algorithm>
#include <cassert>
#include <concepts>
#include <expected>
#include <filesystem>
#include <memory>
#include <ranges>
#include <span>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

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

// Templates:
template <FW::LScript::LuaType LuaValue>
[[nodiscard]] std::expected<LuaValue, FW::LScript::LuaPullValErr>
FW::LScript::Inst::get_value_from_script(const std::string &table_path)
{

  assert(!table_path.empty() && "Table path cannot be empty!");
  if (!table_path.empty())
    return std::unexpected(LuaPullValErr::TABLE_PATH_EMPTY);

  const std::vector<std::string> keys{table_path | std::views::split('.') |
                                      std::ranges::to<std::vector<std::string>>()};

  constexpr auto STACK_TOP{-1};
  auto get_value = [this]() -> std::expected<LuaValue, FW::LScript::LuaPullValErr>
  {
    if constexpr (std::is_same_v<LuaValue, bool>)
    {
      const auto value{lua_toboolean(lua_.get(), STACK_TOP)};
      lua_settop(lua_.get(), 0);
      return value;
    }
    else if constexpr (!std::is_same_v<LuaValue, bool> && std::is_arithmetic_v<LuaValue>)
    {
      const auto value{lua_tonumber(lua_.get(), STACK_TOP)};
      lua_settop(lua_.get(), 0);
      return value;
    }
    else if constexpr (std::same_as<LuaValue, std::string>)
    {
      const auto value{lua_tostring(lua_.get(), STACK_TOP)};
      if (value == nullptr)
      {
        lua_settop(lua_.get(), 0);
        return std::unexpected(LuaPullValErr::RECIEVED_STRING_IS_NULL);
      }

      lua_settop(lua_.get(), 0);
      return value;
    }
  };

  auto return_val = [this](const LuaValue value) -> LuaValue
  {
    lua_settop(lua_.get(), 0);
    return value;
  };

  // Global:
  if (keys.size() == 1)
  {
    constexpr auto FIRST{0};
    const auto global_type{lua_getglobal(lua_.get(), keys.at(FIRST).c_str())};

    if (global_type == LUA_TNIL)
      return std::unexpected(LuaPullValErr::GLOBAL_DOES_NOT_EXIST);
    else
    {
      return return_val(get_value());
    }
  }
  else
  {
    // Iterate through list:
    const auto top_field{[this](const std::span<const std::string> keys)
                         {
                           for (const auto &key : keys)
                           {
                             lua_getfield(lua_.get(), STACK_TOP, key.c_str());
                           }
                         }(keys)};
  }

  return return_val(get_value());
}

namespace FW::LScript {
  [[nodiscard]] bool execute_file_list(Inst &instance, const std::span<const std::filesystem::path> file_list) noexcept;
}
