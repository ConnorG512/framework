#include "errors.hpp"
#include "instance.hpp"
#include "lauxlib.h"
#include "lua.h"
#include "types.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <expected>
#include <ranges>
#include <string>
#include <variant>
#include <vector>

namespace
{
auto clear_stack = [](lua_State *lua)
{
  assert(lua != nullptr && "Lua instance is null when clearing stack!");
  lua_settop(lua, 0);
};

auto get_type_at_top = [](lua_State *lua){
  return lua_type(lua, -1);
};
} // namespace

// Private:
lua_State *FW::LS::Inst::create()
{
  auto *new_lua_state{luaL_newstate()};
  assert(new_lua_state != nullptr && "Lua state failed to be created!");
  return (new_lua_state != nullptr) ? new_lua_state : nullptr;
}

void FW::LS::Inst::close(lua_State *lua_state_ptr)
{
  assert(lua_state_ptr != nullptr && "Lua state pointer is null on destruction!");
  lua_close(lua_state_ptr);
  lua_state_ptr = nullptr;
}

// Public:
[[nodiscard]] bool FW::LS::Inst::execute_file(const std::filesystem::path &path_to_file) noexcept
{
  assert(lua_.get() != nullptr && "Lua instance is nullptr!");

  const auto result{luaL_dofile(lua_.get(), path_to_file.c_str())};
  if (result != LUA_OK)
    return false;
  else
    return true;
}

[[nodiscard]] std::expected<void, FW::LS::LuaCPushErr>
FW::LS::Inst::register_function(const FuncRegData &reg_data) noexcept
{
  if (reg_data.lua_func == nullptr) [[unlikely]]
  {
    assert(false && "Function pointer is null!");
    return std::unexpected(LuaCPushErr::FUNC_IS_NULLPTR);
  }
  else if (reg_data.signature == nullptr) [[unlikely]]
  {
    assert(false && "Function signature is null!");
    return std::unexpected(LuaCPushErr::SIGNATURE_IS_NULLPTR);
  }

  assert(lua_.get() != nullptr && "Lua instance is nullptr!");

  lua_register(lua_.get(), reg_data.signature, reg_data.lua_func);
  return {};
}

[[nodiscard]] std::expected<std::variant<std::string, double, std::int32_t, bool>, FW::LS::LuaPullValErr>
FW::LS::Inst::get_value(const std::string &key_path) noexcept
{
  if(key_path.empty()) [[unlikely]]
  {
    assert(false && "Keypath should not be empty!");
    return std::unexpected(FW::LS::LuaPullValErr::TABLE_PATH_EMPTY);
  }

  const std::vector<std::string> keys{key_path | std::views::split('.') | std::ranges::to<std::vector<std::string>>()};
  
  constexpr auto STACK_TOP{-1};
  auto return_valid_type = [this](const int found_type) -> std::variant<std::string, double, std::int32_t, bool> {
    if (found_type == LUA_TSTRING)
    {
      const auto result{lua_tostring(lua_.get(), STACK_TOP)};
      clear_stack(lua_.get());
      return result;
    }
    else if (found_type == LUA_TNUMBER)
    {
      if (lua_isinteger(lua_.get(), STACK_TOP))
      {
        const auto result{lua_tointeger(lua_.get(), STACK_TOP)};
        clear_stack(lua_.get());
        return static_cast<std::int32_t>(result);
      }
      else 
      {
        const auto result{lua_tonumber(lua_.get(), STACK_TOP)};
        clear_stack(lua_.get());
        return result;
      }
    }
    else if (found_type == LUA_TBOOLEAN)
    {
      const auto result{lua_toboolean(lua_.get(), STACK_TOP)};
      clear_stack(lua_.get());
      return result;
    }
    else 
      return -1;
  };

  if (keys.size() == 1)
  {
    constexpr auto FIRST{0};
    const auto found_type{lua_getglobal(lua_.get(), keys.at(FIRST).c_str())};
    clear_stack(lua_.get());
    return return_valid_type(found_type);
  }
  else
  {
    auto find_leaf_value =
        std::ranges::find_if(keys, [this](const std::string &key)
                             { return (lua_getfield(lua_.get(), STACK_TOP, key.c_str()) != LUA_TTABLE); });
    if (find_leaf_value == keys.end())
    {
      clear_stack(lua_.get());
      return std::unexpected(LuaPullValErr::LEAF_VAL_DOES_NOT_EXIST);
    }
    else
    {
      const auto leaf_type = get_type_at_top(lua_.get());
      clear_stack(lua_.get());
      return return_valid_type(leaf_type);
    }
  }
}
