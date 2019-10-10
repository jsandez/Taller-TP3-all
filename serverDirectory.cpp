#include <iostream>
#include <string>
#include "serverDirectory.h"

serverDirectory::serverDirectory() {}

void serverDirectory::addFile(std::string name) {
  this->set_files.insert(name);
}

bool serverDirectory::isFile(std::string name) {
  return (this->set_files.find(name) != this->set_files.end());
}

void serverDirectory::deleteFile(std::string name) {
  this->set_files.erase(name);
}

std::string serverDirectory::getDirectory(std::string format) {
  std::string msg_return;
  for (std::string file:this->set_files) {
    msg_return = msg_return + format + " " + file + "\n";
  }
  return std::move(msg_return);
}
