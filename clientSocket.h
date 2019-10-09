#ifndef _SOCKETCLIENT_H_
#define _SOCKETCLIENT_H_
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>

class clientSocket {
 private:
  int fd;
  void __getHostAddrInfo(std::string host, std::string service, addrinfo **ai_list);
 public:
  clientSocket(std::string host, std::string service);
  void sendMsg(const std::string msg);
  void recvMsg(std::string &msg);
  ~clientSocket();
};

#endif
