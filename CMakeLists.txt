cmake_minimum_required(VERSION 3.0)

project(BasicLog)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(
    BasicLog INTERFACE
    src/basic_log.h
)

add_executable(
    BasicLogTest
    src/main.cpp
)

target_link_libraries(BasicLogTest PRIVATE BasicLog)

install(
    TARGETS BasicLog
    EXPORT BasicLogTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)
install(
    EXPORT BasicLogTargets
    FILE BasicLogTargets.cmake
    NAMESPACE BasicLog::
    DESTINATION lib/cmake/BasicLog
)
install(
    DIRECTORY src/
    DESTINATION include/BasicLog
    FILES_MATCHING PATTERN "*.h"
)
