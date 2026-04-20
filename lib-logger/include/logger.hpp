#pragma once 

#include <filesystem>
#include <fstream>

namespace FW::Log {
  class Instance {
    public:
      explicit Instance(const std::filesystem::path &path);
      Instance() = default;
    
    private:
      std::ofstream file_ {"application.log", std::ios::trunc};
  };
};
