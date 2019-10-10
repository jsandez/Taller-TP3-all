#include "serverInputFileException.h"

serverInputFileException::serverInputFileException(std::string msg) noexcept : msg(msg), __errno(errno)  {}

const char *serverInputFileException::what() const noexcept {
  return this->msg.c_str();
}
