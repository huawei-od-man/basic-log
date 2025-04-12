#include "basic_log.h"

int main(int argc, char const *argv[])
{
    // Set the logging level to INFO
    Logging::BasicConfig(Logging::INFO);
    LOG(INFO) << "This is an info message";
    LOG(DEBUG) << "This debug message will not be shown";
    LOG(WARN) << "This is a warning message" << false;
    return 0;
}
