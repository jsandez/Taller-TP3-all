#ifndef _COMMONSOCKET_H_
#define _COMMONSOCKET_H_
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>

class commonSocket {
 private:
  int fd;
  static void __getAddrInfo(const char *, std::string service, addrinfo **ai_list);
  void __bindAddress(addrinfo *ai_list);
  commonSocket(int fd);

 public:
  commonSocket();
  void connect(std::string host, const std::string &service);
  void bindAndListen(const std::string &service, int max_waiting_clients);
  commonSocket accept();
  void sendMsg(const std::string &msg);
  void recvMsg(std::string &msg, const char &delimiter);
  void shutdownSocket();
  void closeSocket();
  commonSocket(const commonSocket &other) = delete;
  commonSocket &operator=(const commonSocket &other) = delete;
  commonSocket(commonSocket &&other);
  commonSocket &operator=(commonSocket &&other);
  ~commonSocket();
};

#endif
