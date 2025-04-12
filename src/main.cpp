#include "basic_log.h"

int main(int argc, char const *argv[])
{
    // Set the logging level to INFO
    Logging::BasicConfig(Logging::INFO);
    LOG(INFO) << "This is an info" << 11 <<  "message" << 3.14555;
    LOG(DEBUG) << "This debug message will not be shown";
    LOG(WARN) << "This is a warning message" << false;

    std::vector<int> vec = {1, 2, 3, 4, 5};
    LOG(INFO) << "Vector:" << vec;

    LOG(ERROR) << "This is an error message" << std::make_pair(1, 2);

    LOG(FATAL) << "This is a fatal message" << std::map<std::string, int>{{"key1", 1}, {"key2", 2}};
    
    return 0;
}
