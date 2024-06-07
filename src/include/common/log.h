#ifndef TINYRPC_LOG_H
#define TINYRPC_LOG_H

#include <cstdint>
#include <ctime>
#include <memory>
#include <queue>
#include <string>

#define DEBUGLOG(msg)                                                         \
  if (auto logger = tinyrpc::Logger::GetGlobaLogger();                        \
      tinyrpc::kDebug >= logger->GetSetLevel()) {                             \
    auto event = tinyrpc::LogEvent(tinyrpc::kDebug, __FILE__, __LINE__, msg); \
    logger->PushLog(event);                                                   \
    logger->Print();                                                          \
  }

#define INFOLOG(msg)                                                         \
  if (auto logger = tinyrpc::Logger::GetGlobaLogger();                       \
      tinyrpc::kInfo >= logger->GetSetLevel()) {                             \
    auto event = tinyrpc::LogEvent(tinyrpc::kInfo, __FILE__, __LINE__, msg); \
    logger->PushLog(event);                                                  \
    logger->Print();                                                         \
  }

#define ERRORLOG(msg)                                                         \
  if (auto logger = tinyrpc::Logger::GetGlobaLogger();                        \
      tinyrpc::kError >= logger->GetSetLevel()) {                             \
    auto event = tinyrpc::LogEvent(tinyrpc::kError, __FILE__, __LINE__, msg); \
    logger->PushLog(event);                                                   \
    logger->Print();                                                          \
  }

namespace tinyrpc {

enum LogLevel : uint8_t { kDebug, kInfo, kError };

auto LogLevelToString(LogLevel level) -> std::string;

auto StringToLogLevel(const std::string &level) -> LogLevel;

auto LogEvent(LogLevel level, const std::string &file_name, int file_line,
              const std::string &msg) -> std::string;

class Logger {
 public:
  static auto GetGlobaLogger() -> std::shared_ptr<Logger>;

  auto GetSetLevel() -> LogLevel { return set_level_; }

  /** 将日志放入 */
  void PushLog(const std::string &event);

  /** 打印日志 */
  void Print();
  Logger(Logger &logger) = delete;

 private:
  explicit Logger(LogLevel level) : set_level_(level) {}

  LogLevel set_level_;
  std::queue<std::string> buffer_;
};
}  // namespace tinyrpc

#endif