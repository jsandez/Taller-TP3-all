#ifndef _COMMONSOCKETEXCEPTION_H_
#define _COMMONSOCKETEXCEPTION_H_
#include <string>
/*
 * Excepcion especializada para los sockets
 */
class commonSocketException : public std::exception {
 private:
  std::string msg;
  int __errno;
 public:
  commonSocketException(std::string msg) noexcept;
  virtual const char *what() const noexcept;
};

#endif
