#include "Logger.hpp"

Logger::Logger() {
}

Logger::Logger(const Logger&) {
}

void Logger::info(const char* str) const {
  std::cerr << str << std::endl;
}
