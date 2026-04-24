#pragma once

#include "errors.hpp"
#include "files.hpp"
#include "instance.hpp"

#include <cassert>

[[nodiscard]] std::expected<std::uint32_t, FW::LS::ExecFileErr>
FW::LS::execute_multiple_files(Inst &instance, const std::filesystem::path &root_path,
                               const std::span<const std::filesystem::path> file_names) noexcept
{
  if (root_path.empty()) [[unlikely]]
  {
    assert(false && "Root path should not be empty!");
    return std::unexpected(ExecFileErr::EMPTY_ROOT_PATH);
  }
  else if (file_names.empty()) [[unlikely]]
  {
    assert(false && "List of file names should not be empty!");
    return std::unexpected(ExecFileErr::EMPTY_FILE_LIST);
  }

  return [&]() -> std::expected<std::uint32_t, FW::LS::ExecFileErr>
  {
    std::uint32_t file_count{0};

    for (const auto &name : file_names)
    {
      if (!instance.execute_file(root_path / name))
        return std::unexpected(ExecFileErr::FAILED_TO_EXEC_LUA_FILE);
      file_count++;
    }

    return file_count;
  }();
}
