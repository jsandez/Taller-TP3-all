#ifndef _SOCKETSERVER_H_
#define _SOCKETSERVER_H_
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string>

/*
 * Socket especializado para manejar conexiones,
 * enviar y recibir mensajes
 * desde el lado del servidor
 */
class serverSocket {
 private:
  int fd;
  static void __getSrvAddrInfo(std::string service, addrinfo **ai_list);
  void __bindAddress(addrinfo *ai_list);
  serverSocket(int fd);

 public:
  serverSocket(std::string service);
  serverSocket accept();
  void sendMsg(const std::string msg);
  void recvMsg(std::string &msg);
  void shutdownSocket();
  void closeSocket();
  serverSocket(const serverSocket &other) = delete;
  serverSocket &operator=(const serverSocket &other) = delete;
  serverSocket(serverSocket &&other);
  serverSocket &operator=(serverSocket &&other);
  ~serverSocket();
};

#endif
