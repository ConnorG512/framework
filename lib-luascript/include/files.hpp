#pragma once

#include "errors.hpp"

#include <cstdint>
#include <expected>
#include <filesystem>

namespace FW::LS
{
class Inst;

[[nodiscard]] std::expected<std::uint32_t, ExecFileErr>
execute_multiple_files(Inst &instance, const std::filesystem::path &root_path,
                       const std::span<const std::filesystem::path> file_names) noexcept;

} // namespace FW::LS
