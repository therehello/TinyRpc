#include "common/log.h"
#include <bits/types/struct_timeval.h>
#include <sys/time.h>
#include <ctime>
#include <format>
#include <iomanip>
#include <iostream>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include "common/config.h"
#include "common/util.h"

namespace tinyrpc {

auto LogLevelToString(LogLevel level) -> std::string {
  switch (level) {
    case kDebug:
      return "DEBUG";
    case kInfo:
      return "INFO";
    case kError:
      return "ERROR";
  }
}

auto StringToLogLevel(const std::string &level) -> LogLevel {
  if (level == "INFO") {
    return kInfo;
  }
  if (level == "ERROR") {
    return kError;
  }
  return kDebug;
}

/**
 * @brief 日志事件
 * 生成统一的日志消息
 */
auto LogEvent(LogLevel level, const std::string &file_name,
              const int32 file_line, const std::string &msg) -> std::string {
  timeval now_time;
  gettimeofday(&now_time, nullptr);
  auto now_tm = localtime(&(now_time.tv_sec));
  auto ms = now_time.tv_usec / 1000;
  std::ostringstream oss;
  oss << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S.") << ms;
  auto time_str = oss.str();

  /** eg. [DEBUG][2024-05-31 18:11:32.408][10378:10378][../test/main.cpp:6] This
   * is a example text. */
  return std::format("[{}][{}][{}:{}][{}:{}]\t{}\n", LogLevelToString(level),
                     time_str, GetPid(), GetThreadId(), file_name, file_line,
                     msg);
}

auto Logger::GetGlobaLogger() -> std::shared_ptr<Logger> {
  static std::shared_ptr<Logger> logger(
      new Logger(StringToLogLevel(Config::GetGlobalConfig()->GetLogLevel())));
  return logger;
}

void Logger::PushLog(const std::string &event) {
  std::lock_guard<std::mutex> guard(lock_);
  std::cout << event;
  buffer_.push(event);
}

}  // namespace tinyrpc
