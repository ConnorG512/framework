#include "instance.hpp"
#include "types.hpp"

#include <cassert>

namespace FW::LS {
  std::expected<void, FW::LS::LuaCPushErr> register_function_list(Inst &lua_instance,
                                                                          const std::span<const FuncRegData> func_list)
  {
    if (func_list.empty()) [[unlikely]]
    {
      assert(false && "Function list should not be empty!");
      return std::unexpected(FW::LS::LuaCPushErr::LIST_EMPTY);
    }
    else
    {
      for (const auto c_func : func_list)
        if (const auto reg_status = lua_instance.register_function(c_func); !reg_status.has_value())
          return std::unexpected(reg_status.error());

      return {};
    }
  }
}

