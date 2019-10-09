#ifndef _SOCKETSERVEREXCEPTION_H_
#define _SOCKETSERVEREXCEPTION_H_
#include <exception>
#include <string>

/*
 * Excepccion especializada para los sockets
 */
class serverSocketException : public std::exception {
 private:
  std::string msg;
  int __errno;
 public:
  serverSocketException(std::string msg) noexcept;
  virtual const char *what() const noexcept;
  ~serverSocketException();
};

#endif
