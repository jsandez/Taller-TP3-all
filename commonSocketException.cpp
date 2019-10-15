#include "commonSocketException.h"

commonSocketException::commonSocketException(std::string msg) noexcept : msg(msg),
                                                                         __errno(errno) {}

const char *commonSocketException::what() const noexcept {
  return this->msg.c_str();
}