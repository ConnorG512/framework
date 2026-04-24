#pragma once

#include "errors.hpp"
#include "types.hpp"

#include <expected>
#include <filesystem>
#include <memory>
#include <variant>

namespace FW::LS
{
class Inst
{
public:
  [[nodiscard]] std::expected<void, LuaCPushErr> register_function(const FuncRegData &reg_data) noexcept;
  [[nodiscard]] bool execute_file(const std::filesystem::path &path_to_file) noexcept;
  [[nodiscard]] std::expected<std::variant<double, std::string, bool>, LuaPullValErr>
  pull_global_value(PulledTypes type, const std::string &name);

private:
  static lua_State* create();
  static void close(lua_State* lua_state_ptr);

  std::unique_ptr<lua_State, decltype(&Inst::close)> lua_ {Inst::create(), &Inst::close};
};
}; // namespace FW::LS


//lua_State *lua_{nullptr};
