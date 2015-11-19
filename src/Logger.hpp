#ifndef NOTHX_LOGGER_HPP
#define NOTHX_LOGGER_HPP

#include <iostream>

/**
 * Logger class
 */

class Logger {
public:

  /**
   * \return the unique instance of Logger
   */
  static Logger& get() {
    static Logger logger;
    return logger;
  }

  /**
   * Displays a message
   */
  void info(const char* str) const;
  
private:
  Logger();
  Logger(const Logger&);

  Logger& operator=(const Logger&) {
    return Logger::get();
  };
};
#endif
