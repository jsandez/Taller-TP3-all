#include "serverMonitorDirectory.h"

serverMonitorDirectory::serverMonitorDirectory(serverDirectory &directory, serverCfgMap &cfg_map)
    : directory(directory), cfg_map(cfg_map) {}

std::string serverMonitorDirectory::addUniq(std::string dir_name) {
  std::lock_guard<std::mutex> l(m);
  if (this->directory.isFile(dir_name)) {
    return "550 " + this->cfg_map.get("mkdFailed") + "\n";
  } else {
    this->directory.addFile(dir_name);
    return "257 \"" + dir_name + "\" " + this->cfg_map.get("mkdSuccess") + "\n";
  }
}

std::string serverMonitorDirectory::removeUniq(std::string dir_name) {
  std::lock_guard<std::mutex> l(m);
  if (this->directory.isFile(dir_name)) {
    this->directory.deleteFile(dir_name);
    return "250 \"" + dir_name + "\" " + this->cfg_map.get("rmdSuccess") + "\n";
  } else {
    return "550 " + this->cfg_map.get("rmdFailed") + "\n";
  }
}

std::string serverMonitorDirectory::getDirectory(std::string format) {
  std::lock_guard<std::mutex> l(m);
  return this->directory.getDirectory(format);
}
