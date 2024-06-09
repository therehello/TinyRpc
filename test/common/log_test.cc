#include "common/log.h"
#include <format>
#include <thread>
#include <vector>
#include "common/config.h"

/**
 * @brief 多线程日志测试
 * 
 */
void MultithreadedLogging() {
  std::vector<std::thread> threads;
  threads.reserve(20);
  for (int i = 0; i < 20; i++) {
    threads.emplace_back(
        [i]() { ERRORLOG(std::format("This is the {}-th test message", i)); });
  }
  for (auto &t : threads) {
    t.join();
  }
}

auto main() -> int {
  tinyrpc::Config::SetGlobalConfig("/workspaces/TinyRpc/conf/config.xml");

  MultithreadedLogging();
}