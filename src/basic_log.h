#ifndef BASIC_LOG_H
#define BASIC_LOG_H

#include <atomic>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

class Logging {
 public:
  enum LogLevel { DEBUG, INFO, WARN, ERROR, FATAL };

  Logging(LogLevel level, std::string_view level_str, std::string_view file,
           int line)
      : level(level) {
    if (level < current_level) {
      return;  // Skip logging if the level is lower than the current level
    }
    oss << "[" << level_str << "]";
    // Get current time
    std::time_t now = std::time(nullptr);
    std::tm* local_time = std::localtime(&now);
    oss << std::put_time(local_time, "[%Y-%m-%d %H:%M:%S]");
    oss << "[" << file << ":" << line << "]:";
  }

  template <typename T>
  Logging& operator<<(const T& value) {
    if (level < current_level) {
      return *this;  // Skip logging if the level is lower than the current
                     // level
    }
    oss << " " << value;
    return *this;
  }

  Logging& operator<<(bool value) {
    if (level < current_level) {
      return *this;  // Skip logging if the level is lower than the current
                     // level
    }
    oss << " " << (value ? "true" : "false");
    return *this;
  }

  ~Logging() {
    if (level < current_level) {
      return;  // Skip logging if the level is lower than the current level
    }
    std::cerr << oss.str() << std::endl;
  }

  // Prevent copying
  Logging(const Logging&) = delete;
  Logging& operator=(const Logging&) = delete;
  // Prevent moving
  Logging(Logging&&) = delete;
  Logging& operator=(Logging&&) = delete;

  static void BasicConfig(LogLevel level) {
    // Set the logging level here if needed
    current_level = level;
  }

 private:
  static inline std::atomic<LogLevel> current_level{DEBUG};
  LogLevel level;
  std::ostringstream oss;
};

#define LOG(level) Logging(Logging::level, #level, __FILE__, __LINE__)

#endif  // BASIC_LOG_H
