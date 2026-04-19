#include "filesystem.hpp"

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
