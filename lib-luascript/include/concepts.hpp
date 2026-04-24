#pragma once 

#include <concepts>
#include <string>
#include <type_traits>

namespace FW::LS {
  template <typename T>
    concept LuaType = std::is_arithmetic_v<T> || std::same_as<T, std::string>;
};
