#include "Logger.hpp"

Logger::Logger() {
}

Logger::Logger(const Logger&) {
}

void Logger::info(const char* str) const {
  std::cerr << "INFO >> " << str << std::endl;
}

void Logger::info(std::string str) const {
  info(str.c_str());
}
