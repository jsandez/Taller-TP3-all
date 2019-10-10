#include "serverSocketException.h"

serverSocketException::serverSocketException(std::string msg) noexcept : msg(msg), __errno(errno) {}

const char *serverSocketException::what() const noexcept {
  return this->msg.c_str();
}
