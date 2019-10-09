#include "clientSocketException.h"

clientSocketException::clientSocketException(std::string msg) noexcept : msg(msg), __errno(errno) {}

const char *clientSocketException::what() const noexcept {
  return this->msg.c_str();
}

clientSocketException::~clientSocketException() {}