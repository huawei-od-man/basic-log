#include "basic_log.h"

#include <chrono>

using namespace std::chrono_literals;

int main(int argc, char const *argv[]) {
  // Set the logging level to INFO
  Logging::BasicConfig(Logging::INFO);
  LOG(INFO) << "This is an info" << 11 << "message" << 3.14555;
  LOG(DEBUG) << "This debug message will not be shown";
  LOG(WARN) << "This is a warning message" << false;

  std::vector<int> vec = {1, 2, 3, 4, 5};
  LOG(INFO) << "Vector:" << vec;

  LOG(ERROR) << "This is an error message" << std::make_pair(1, 2);

  LOG(FATAL) << "This is a fatal message"
             << std::map<std::string, int>{{"key1", 1}, {"key2", 2}};

  LOG(FATAL) << "This is a fatal message" << std::set<int>{1, 2, 3};

  LOG(FATAL) << "This is a fatal message"
             << std::unordered_map<std::string, int>{{"key1", 1}, {"key2", 2}};
  LOG(FATAL) << "This is a fatal message" << std::optional<int>{std::nullopt};
  LOG(FATAL) << "This is a fatal message" << std::optional<int>{42};
  LOG(FATAL) << "This is a fatal message"
             << std::optional<std::string>{"Hello, World!"};

  LOG(FATAL) << "This is a fatal message" << 1s;

    LOG(FATAL) << "This is a fatal message" << std::chrono::milliseconds(1000);

    LOG(FATAL) << "This is a fatal message" << std::chrono::microseconds(1000);

    LOG(FATAL) << "This is a fatal message" << std::chrono::nanoseconds(1000);

    LOG(FATAL) << "This is a fatal message" << std::chrono::hours(1);

    LOG(FATAL) << "This is a fatal message" << std::chrono::minutes(1);

    LOG(FATAL) << "This is a fatal message" << std::chrono::seconds(1);

    LOG(FATAL) << "This is a fatal message" << std::chrono::system_clock::now();

  return 0;
}
