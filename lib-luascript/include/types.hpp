#pragma once 

struct lua_State; // Forward

namespace FW::LS {
  struct FuncRegData
  {
    int (*lua_func)(lua_State *){nullptr};
    const char *signature{nullptr};
  };

  enum class PulledTypes {
    BOOLEAN,
    NUMBER,
    STRING,
  };
}
