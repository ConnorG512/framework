#pragma once

namespace FW::LS
{
enum class LuaCPushErr
{
  FUNC_IS_NULLPTR,
  SIGNATURE_IS_NULLPTR,
  LIST_EMPTY,
};

enum class LuaPullValErr
{
  TABLE_PATH_EMPTY,
  NO_VALID_RETURN_VALUE,
  RECIEVED_STRING_IS_NULL,
  GLOBAL_VAL_DOES_NOT_EXIST,
  LEAF_VAL_DOES_NOT_EXIST,
};

enum class ToTypeErr {
  EMPTY_KEY,
  CANNOT_FIND_VALID_TYPE,
};

enum class ExecFileErr{
  EMPTY_ROOT_PATH,
  EMPTY_FILE_LIST,
  FAILED_TO_EXEC_LUA_FILE,
};
} // namespace FW::LS
