#include "logger.hpp"
#include <cassert>
#include <fstream>
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

auto close_log = [](std::ofstream &log_file)
{
  assert(log_file.is_open() && "Log file should be open when calling close!");
  if (log_file.is_open())
  {
    std::println(log_file, "Closing log file...");
    log_file.close();
  }
};

auto has_hit_max_writes = [](const std::uint32_t max, const std::uint32_t current) { return (current >= max); };

} // namespace

FW::Log::Instance::Instance(const std::filesystem::path &path, const std::uint32_t max_writes)
    : file_{path, std::ios::trunc}, max_writes_{max_writes}
{
}

void FW::Log::Instance::write(const Type type, const std::string &message)
{
  assert(!message.empty() && "Log message should not be empty!");

  if (!file_.is_open())
    return;

  if (has_hit_max_writes(max_writes_, current_writes))
  {
    std::println(file_, "Has hit max write limit!");
    close_log(file_);
  }

  std::println(file_, "[{}]: {}.", get_logging_prefix(type), message);
  current_writes += 1;
}
