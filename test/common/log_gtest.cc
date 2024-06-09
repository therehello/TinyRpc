#include <iostream>
#include <regex>
#include "common/config.h"
#include "common/log.h"
#include "gtest/gtest.h"

class LogTest : public testing::Test {
 protected:
  void SetUp() override {
    /** 保存旧的缓冲区指针 */
    saved_cout_stream_ = std::cout.rdbuf();
    /** 将cout的缓冲区指针重定向到文件的缓冲区指针 */
    std::cout.rdbuf(ss_.rdbuf());
  }

  void TearDown() override {
    /** 恢复cout的缓冲区指针 */
    std::cout.rdbuf(saved_cout_stream_);
  }

  std::stringstream ss_;
  std::streambuf *saved_cout_stream_;
};

TEST_F(LogTest, DEBUG) {
  tinyrpc::Config::SetGlobalConfig("/workspaces/TinyRpc/conf/config.xml");
  DEBUGLOG("Test message");
  ASSERT_TRUE(ss_.str().empty());
}

TEST_F(LogTest, INFO) {
  tinyrpc::Config::SetGlobalConfig("/workspaces/TinyRpc/conf/config.xml");
  INFOLOG("Test message");
  auto s = std::format(
      R"(\[INFO\]\[\d{{4}}-\d{{2}}-\d{{2}} \d{{2}}:\d{{2}}:\d{{2}}\.\d{{1,3}}\]\[\d{{5}}:\d{{5}}\]\[{}:{}\]\tTest message\n)",
      __FILE__, __LINE__ - 3);
  std::regex expected_regex(s);
  ASSERT_TRUE(std::regex_search(ss_.str(), expected_regex));
}

TEST_F(LogTest, ERROR) {
  tinyrpc::Config::SetGlobalConfig("/workspaces/TinyRpc/conf/config.xml");
  ERRORLOG("Test message");
  auto s = std::format(
      R"(\[ERROR\]\[\d{{4}}-\d{{2}}-\d{{2}} \d{{2}}:\d{{2}}:\d{{2}}\.\d{{1,3}}\]\[\d{{5}}:\d{{5}}\]\[{}:{}\]\tTest message\n)",
      __FILE__, __LINE__ - 3);
  std::regex expected_regex(s);
  ASSERT_TRUE(std::regex_search(ss_.str(), expected_regex));
}