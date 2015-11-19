#ifndef NOTHX_LOGGER_HPP
#define NOTHX_LOGGER_HPP

#include <iostream>

class Logger {
public:
  static Logger& get() {
    static Logger logger;
    return logger;
  }

  void info(const char* str) const;
  
private:
  Logger();
  Logger(const Logger&);

  Logger& operator=(const Logger&) {
    return Logger::get();
  };
};
#endif
