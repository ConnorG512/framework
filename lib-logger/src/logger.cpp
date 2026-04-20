#include "logger.hpp"
#include <cassert>
#include <print>

namespace
{
[[nodiscard]] std::string_view get_logging_prefix(const FW::Log::Type prefix_type)
{
  switch (prefix_type)
  {
    case FW::Log::Type::ERROR:
      return "ERROR";
    case FW::Log::Type::WARNING:
      return "WARNING";
    case FW::Log::Type::DEBUG:
      return "DEBUG";
    case FW::Log::Type::INFO:
      return "INFO";
    default:
      return "INVALID LOG USE";
  }
}
} // namespace

FW::Log::Instance::Instance(const std::filesystem::path &path) : file_{path, std::ios::trunc} {}

void FW::Log::Instance::write(const Type type, const std::string &message)
{
  assert(!message.empty() && "Log message should not be empty!");
  std::println(file_, "[{}]: {}.", get_logging_prefix(type), message);
}
