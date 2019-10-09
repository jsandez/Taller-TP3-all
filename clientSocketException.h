#ifndef _SOCKETCLIENTEXCEPTION_H_
#define _SOCKETCLIENTEXCEPTION_H_
#include <exception>
#include <string>

class clientSocketException : public std::exception {
 private:
  std::string msg;
  int __errno;
 public:
  clientSocketException(std::string msg) noexcept;
  virtual const char *what() const noexcept;
  ~clientSocketException();
};
#endif
