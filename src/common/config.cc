#include "common/config.h"
#include <cstdlib>
#include <format>
#include <iostream>
#include <memory>
#include <string>
#include "tinyxml2/tinyxml2.h"

namespace tinyrpc {

static std::shared_ptr<Config> config;

auto Config::GetGlobalConfig() -> std::shared_ptr<Config> {
  if (config == nullptr) {
    std::cerr << "Error: Configuration file path not provided. Please use "
                 "tinyrpc::Config::SetGlobalConfig to set the configuration "
                 "file path "
                 "before continuing.\n";
    exit(1);
  }
  return config;
}

void Config::SetGlobalConfig(const std::string &xml_file) {
  config = std::shared_ptr<Config>(new Config(xml_file));
}

static auto GetSonNode(auto &father,
                       const std::string &name) -> tinyxml2::XMLElement * {
  auto son = father->FirstChildElement(name.c_str());
  if (!son) {
    std::cerr << std::format(
        "Start TinyRpc server error, failed to read node {}\n", name);
    exit(1);
  }
  return son;
}

Config::Config(const std::string &xml_file) {
  auto doc = std::make_unique<tinyxml2::XMLDocument>();
  if (doc->LoadFile(xml_file.c_str()) != 0) {
    std::cerr << std::format(
        "Start TinyRpc server error, failed to read config file \"{}\"\n",
        xml_file);
    exit(1);
  }
  auto root_node = GetSonNode(doc, "root");
  auto log_node = GetSonNode(root_node, "log");
  auto log_level_node = GetSonNode(log_node, "log-level");
  log_level_ = log_level_node->GetText();
}
}  // namespace tinyrpc