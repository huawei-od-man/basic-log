# basic_log

`basic_log` 是一个用 C++ 编写的轻量级日志记录库，旨在为开发者提供简单、高效的日志记录功能。

## 功能

- **多级日志支持**：支持日志级别如 `INFO`、`DEBUG`、`WARN` 和 `ERROR`。
- **轻量高效**：适用于嵌入式系统或资源受限的环境。
- **可配置输出**：支持将日志输出到控制台、文件或其他自定义目标。
- **线程安全**：在多线程环境中安全使用。

## 编译与运行

### 前置要求

- C++17 或更高版本的编译器（如 `g++` 或 `clang++`）。
- CMake（可选，用于构建项目）。

### 使用 CMake 构建

1. 克隆项目到本地：

   ```bash
   git clone https://github.com/your-username/basic-log.git
   cd basic-log
   ```

2. 创建构建目录并运行 CMake：

   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

3. 运行示例程序（如果有）：

   ```bash
   ./basic_log_example
   ```

### 手动编译

如果不使用 CMake，可以直接使用编译器：

```bash
g++ -std=c++17 -o basic_log_example src/main.cpp src/basic_log.cpp
```

## 使用方法

以下是一个简单的示例代码：

```cpp
#include "basic_log.h"

int main(int argc, char const *argv[])
{
    // Set the logging level to INFO
    Logging::BasicConfig(Logging::INFO);
    LOG(INFO) << "This is an info" << 11 <<  "message" << 3.14555;
    LOG(DEBUG) << "This debug message will not be shown";
    LOG(WARN) << "This is a warning message" << false;
    return 0;
}
```

## 贡献

欢迎贡献代码！请按照以下步骤提交您的更改：

1. Fork 本仓库。
2. 创建一个分支：`git checkout -b feature/your-feature-name`。
3. 提交更改：`git commit -m '描述您的更改'`。
4. 推送分支：`git push origin feature/your-feature-name`。
5. 创建一个 Pull Request。

## 许可证

本项目基于 [MIT License](LICENSE) 开源。

