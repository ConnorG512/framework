#pragma once

#include "errors.hpp"
#include "types.hpp"

#include <expected>
#include <span>

namespace FW::LS
{
class Inst;
}

namespace FW::LS
{

std::expected<void, FW::LS::LuaCPushErr> register_function_list(Inst &lua_instance,
                                                                const std::span<const FuncRegData> func_list);
}
