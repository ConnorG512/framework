#pragma once

#include <expected>

#include <filesystem>
#include <span>
namespace FW::FS
{
enum class ExistsErrors
{
  PATH_EMPTY,
  COLLECTION_EMPTY,
  PATH_DOES_NOT_EXIST,
};
[[nodiscard]] std::expected<bool, ExistsErrors> exists(const std::filesystem::path &path_to_item) noexcept;
[[nodiscard]] std::expected<void, ExistsErrors>
validate_paths(const std::span<const std::filesystem::path> item_collection) noexcept;

enum class DataPathError {
  NULL_ENV_VAR,
};
[[nodiscard]] std::expected<std::filesystem::path, DataPathError> get_system_path(const std::string &app_path_name = "fw") noexcept;
[[nodiscard]] std::expected<std::filesystem::path, DataPathError> get_custom_path(const std::string &app_path_name = "fw") noexcept;
} // namespace FW::FS
