#pragma once

#include <filesystem>
#include <fstream>

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
  explicit Instance(const std::filesystem::path &path);
  Instance() = default;

  void write(const FW::Log::Type type, const std::string &message);

private:
  std::ofstream file_{"application.log", std::ios::trunc};
};
}; // namespace FW::Log
