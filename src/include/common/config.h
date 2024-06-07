#ifndef TINYRPC_CONFIG_H
#define TINYRPC_CONFIG_H

#include <cstdint>
#include <memory>
#include <string>

namespace tinyrpc {
using int32 = std::int32_t;

class Config {
 public:
  static auto GetGlobalConfig() -> std::shared_ptr<Config>;

  static void SetGlobalConfig(const std::string &xml_file);

  auto GetLogLevel() -> std::string { return log_level_; }

  Config(Config &config) = delete;

 private:
  explicit Config(const std::string &xml_file);

  /** 日志等级 */
  std::string log_level_{"Debug"};
};
}  // namespace tinyrpc

#endif