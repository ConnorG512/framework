#pragma once

namespace FW::LS
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
} // namespace FW::LS
