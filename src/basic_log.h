#ifndef BASIC_LOG_H
#define BASIC_LOG_H

#include <atomic>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

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

  /**
   * * @brief Overload for boolean values.
   * * @details This overload allows logging boolean values as "true" or
   * "false". It checks the current logging level and skips logging if the
   * level is lower than the current level.
   * * @param value The boolean value to log.
   * * @return A reference to the Logging object for chaining.
   */
  Logging& operator<<(bool value) {
    if (level < current_level) {
      return *this;  // Skip logging if the level is lower than the current
                     // level
    }
    oss << " " << (value ? "true" : "false");
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

 private:
  /// @brief The current logging level.
  static inline std::atomic<LogLevel> current_level{DEBUG};
  /// @brief  The logging level for this instance.
  LogLevel level;
  std::ostringstream oss;
};

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
#define LOG(level) Logging(Logging::level, #level, __FILE__, __LINE__)

#endif  // BASIC_LOG_H
