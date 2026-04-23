#include "filesystem.hpp"

#include <cassert>
#include <cstdlib>
#include <filesystem>
#include <print>

[[nodiscard]] std::expected<bool, FW::FS::ExistsErrors>
FW::FS::exists(const std::filesystem::path &path_to_item) noexcept
{
  if (path_to_item.empty())
    return std::unexpected(ExistsErrors::PATH_EMPTY);

  return std::filesystem::exists(path_to_item);
}

[[nodiscard]] std::expected<void, FW::FS::ExistsErrors>
validate_paths(const std::span<const std::filesystem::path> item_collection) noexcept
{
  if (item_collection.empty())
    return std::unexpected(FW::FS::ExistsErrors::COLLECTION_EMPTY);

  for (const auto &path : item_collection)
  {
    if (!std::filesystem::exists(path))
    {
      std::println(stderr, "Path [{}] does not exist!", path.string());
      return std::unexpected(FW::FS::ExistsErrors::PATH_DOES_NOT_EXIST);
    }
  }
  return {};
}

[[nodiscard]] std::expected<std::filesystem::path, FW::FS::DataPathError>
get_custom_path(const std::string &app_path_name) noexcept
{
  const auto path{std::getenv("FW_CUSTOM_DATA_PATH")};
  if (path == nullptr)
    return std::unexpected(FW::FS::DataPathError::NULL_ENV_VAR);

  const std::filesystem::path complete_path{std::filesystem::path(path) / app_path_name};
  return complete_path;
}

void create_directories(const std::filesystem::path &path, const std::span<std::string_view> dir_list)
{
  assert(!dir_list.empty() && "Directory list cannot be empty!");

  for (const auto &directory : dir_list)
  {
    assert(!directory.empty() && "Directory name cannot be an empty string!");
    std::filesystem::create_directory(path / directory);
  }
}
