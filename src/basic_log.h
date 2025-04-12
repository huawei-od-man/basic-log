#ifndef BASIC_LOG_H
#define BASIC_LOG_H

#include <atomic>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <optional>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * * @brief A simple logging class that supports different log levels.
 * * @details This class provides a way to log messages with different severity
 * levels (DEBUG, INFO, WARN, ERROR, FATAL). The logging level can be set
 * dynamically, and messages below the current level will not be logged.
 * * @note The logging level can be set using the BasicConfig method. The
 * default level is DEBUG. The logging messages are printed to standard error
 * output.
 * * @example
 * * #include "basic_log.h"
 * * int main(int argc, char const *argv[])
 * * {
 * *     // Set the logging level to INFO
 * *     Logging::BasicConfig(Logging::INFO);
 * *     LOG(INFO) << "This is an info message";
 * *     LOG(DEBUG) << "This debug message will not be shown";
 * *     LOG(WARN) << "This is a warning message" << false;
 * *     return 0;
 * * }
 * * @param level The logging level (DEBUG, INFO, WARN, ERROR, FATAL).
 * * @param level_str The string representation of the logging level.
 * * @param file The name of the source file where the log message is generated.
 * * @param line The line number in the source file where the log message is
 * generated.
 */
class Logging {
 public:
  /**
   * * @brief Enumeration for log levels.
   */
  enum LogLevel { DEBUG, INFO, WARN, ERROR, FATAL };

  Logging() = default;

  Logging(std::string_view level_str, std::string_view file, int line)
      : oss(std::ostringstream()) {
    *oss << "[" << level_str << "]";
    // Get current time
    std::time_t now = std::time(nullptr);
    std::tm* local_time = std::localtime(&now);
    *oss << std::put_time(local_time, "[%Y-%m-%d %H:%M:%S]");
    *oss << "[" << file << ":" << line << "]:";
  }

  Logging& operator<<(void (*manip)(Logging&)) {
    manip(*this);
    return *this;
  }

  static void NoSpace(Logging& log) { log.no_space = true; }

  template <typename T>
  Logging& operator<<(const T& value) {
    if (oss) {
      if (no_space) {
        no_space = false;
      } else {
        *oss << " ";
      }
      *oss << value;
    }
    return *this;
  }

  template <typename T>
  Logging& LogSequence(std::string_view name, T begin, T end) {
    *this << name << NoSpace << "{";
    for (auto it = begin; it != end; ++it) {
      *this << *it;
      if (std::next(it) != end) {
        *this << ",";
      }
    }
    *this << "}";
    return *this;
  }

  template <typename T>
  Logging& LogMapping(std::string_view name, T begin, T end) {
    *this << name << NoSpace << "{";
    for (auto it = begin; it != end; ++it) {
      *this << it->first << ":" << it->second;
      if (std::next(it) != end) {
        *this << ",";
      }
    }
    *this << "}";
    return *this;
  }

  /**
   * * @brief Destructor for the Logging class.
   * * @details The destructor checks the current logging level and prints the
   * log message if the level is higher than or equal to the current level.
   * * @note The destructor is called when the Logging object goes out of
   * scope. It ensures that the log message is printed even if the object is
   * destroyed.
   */
  ~Logging() {
    if (!oss) {
      return;
    }
    std::cerr << oss->str() << std::endl;
  }

  // Prevent copying
  Logging(const Logging&) = delete;
  Logging& operator=(const Logging&) = delete;
  // Prevent moving
  Logging(Logging&&) = delete;
  Logging& operator=(Logging&&) = delete;

  /**
   * * @brief Set the logging level.
   * * @details This method allows setting the logging level dynamically. The
   * logging level can be set to DEBUG, INFO, WARN, ERROR, or FATAL. Messages
   * below the current level will not be logged.
   * * @param level The logging level to set.
   * * @note The default logging level is DEBUG. This method can be used to
   * change the logging level at runtime.
   */
  static void BasicConfig(LogLevel level) {
    // Set the logging level here if needed
    current_level = level;
  }
  static LogLevel GetCurrentLevel() { return current_level; }

 private:
  /// @brief The current logging level.
  static inline std::atomic<LogLevel> current_level{DEBUG};
  bool no_space{false};
  std::optional<std::ostringstream> oss;
};

Logging& operator<<(Logging& log, bool value) {
  return log << (value ? "true" : "false");
}

template <typename K, typename V>
Logging& operator<<(Logging& log, const std::pair<K, V>& value) {
  log << "std::pair{" << value.first << "," << value.second << "}";
  return log;
}

template <typename T>
Logging& operator<<(Logging& log, const std::vector<T>& value) {
  return log.LogSequence("std::vector", value.begin(), value.end());
}

template <typename T>
Logging& operator<<(Logging& log, const std::set<T>& value) {
  return log.LogSequence("std::set", value.begin(), value.end());
}

template <typename K, typename V>
Logging& operator<<(Logging& log, const std::map<K, V>& value) {
  return log.LogMapping("std::map", value.begin(), value.end());
}

template <typename K, typename V>
Logging& operator<<(Logging& log, const std::unordered_map<K, V>& value) {
  return log.LogMapping("std::unordered_map", value.begin(), value.end());
}
template <typename T>
Logging& operator<<(Logging& log, const std::optional<T>& value) {
  if (value.has_value()) {
    return log << "std::optional{" << value.value() << "}";
  } else {
    return log << "std::optional{ nullopt }";
  }
}

Logging& operator<<(Logging& log, std::nullptr_t) { return log << "nullptr"; }

Logging& operator<<(Logging& log, std::nullopt_t) {
  return log << "std::nullopt";
}

Logging& operator<<(Logging& log, std::chrono::seconds value) {
  return log << value.count() << "seconds";
}

Logging& operator<<(Logging& log, std::chrono::milliseconds value) {
  return log << value.count() << "milliseconds";
}

Logging& operator<<(Logging& log, std::chrono::microseconds value) {
  return log << value.count() << "microseconds";
}

Logging& operator<<(Logging& log, std::chrono::nanoseconds value) {
  return log << value.count() << "nanoseconds";
}

Logging& operator<<(Logging& log, std::chrono::hours value) {
  return log << value.count() << "hours";
}

Logging& operator<<(Logging& log, std::chrono::minutes value) {
  return log << value.count() << "minutes";
}

inline Logging& operator<<(Logging& log,
                           std::chrono::system_clock::time_point value) {
  auto time = std::chrono::system_clock::to_time_t(value);
  return log << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
}


/**
 * * @brief Macro to create a logging object.
 * * @details This macro creates a Logging object with the specified log level,
 * file name, and line number. It allows logging messages with different
 * severity levels (DEBUG, INFO, WARN, ERROR, FATAL). The macro expands to a
 * Logging constructor call with the appropriate parameters.
 * * @param level The logging level (DEBUG, INFO, WARN, ERROR, FATAL).
 * * @note This macro is used to simplify the logging process. It allows
 * creating a Logging object with the specified log level, file name, and line
 * number. The macro expands to a Logging constructor call with the
 * appropriate parameters. The log level is specified as a parameter to the
 * macro, and the file name and line number are automatically captured using
 * the __FILE__ and __LINE__ macros. This allows for easy logging of messages
 * with different severity levels without having to manually specify the file
 * name and line number each time. The macro also allows for chaining of
 * logging messages, making it easy to log multiple messages in a single
 * statement.
 */
#define LOG(level)                             \
  (Logging::level < Logging::GetCurrentLevel() \
       ? Logging()                             \
       : Logging(#level, __FILE__, __LINE__))

#endif  // BASIC_LOG_H
