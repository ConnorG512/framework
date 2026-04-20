#pragma once

#include <filesystem>
#include <fstream>
#include <limits>

namespace FW::Log
{
enum class Type
{
  INFO,
  ERROR,
  WARNING,
  DEBUG,
};

class Instance
{
public:
  explicit Instance(const std::filesystem::path &path,
                    const std::uint32_t max_writes = std::numeric_limits<std::uint32_t>::max());
  Instance() = default;

  void write(const FW::Log::Type type, const std::string &message);

private:
  std::ofstream file_{"application.log", std::ios::trunc};
  std::uint32_t max_writes_{std::numeric_limits<std::uint32_t>::max()};
  std::uint32_t current_writes{0};
};
}; // namespace FW::Log
