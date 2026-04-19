#include "filesystem.hpp"
#include <cstdlib>

[[nodiscard]] std::expected<std::filesystem::path, FW::FS::DataPathError>
get_system_path(const std::string &app_path_name) noexcept
{
  const auto system_path{std::getenv("LOCALAPPDATA")};
  if (system_path == nullptr)
    return std::unexpected(FW::FS::DataPathError::NULL_ENV_VAR);
  const std::filesystem::path complete_path{std::filesystem::path(system_path) / app_path_name};
  return complete_path;
}
