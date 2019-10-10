#include <cstring>
#include <stdexcept>
#include <iostream>
#include "clientSocket.h"
#include "clientSocketException.h"

void clientSocket::__getHostAddrInfo(std::string host, std::string service, addrinfo **ai_list) {
  addrinfo hints = {};
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = 0;
  int errcode = getaddrinfo(host.c_str(), service.c_str(), &hints, ai_list);
  if (errcode != 0) {
    throw clientSocketException("ERROR GETADDRINFO " + (std::string) gai_strerror(errcode));
  }
}

clientSocket::clientSocket(std::string host, std::string service) {
  struct addrinfo *ai_list;
  __getHostAddrInfo(host, service, &ai_list);
  bool connected = false;
  for (addrinfo *ptr = ai_list; ptr != NULL && !connected; ptr = ai_list->ai_next) {
    this->fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if (connect(this->fd, ptr->ai_addr, ptr->ai_addrlen) == 0) {
      connected = true;
    }
  }
  freeaddrinfo(ai_list);
  if (!connected) {
    throw clientSocketException("ERROR CONNECT");
  }
}

void clientSocket::sendMsg(const std::string msg) {
  size_t bytes_send = 0;
  while (bytes_send < msg.length()) {
    int valread = ::send(this->fd,
                         &msg[bytes_send],
                         msg.length() - bytes_send,
                         MSG_NOSIGNAL);
    if (valread == -1) {
      std::cout << "socketSend: \n" << strerror(errno) << std::endl;
      shutdown(this->fd, SHUT_RDWR);
      throw clientSocketException("socketSend: " + (std::string) strerror(errno));
    }
    if (valread > 0) {
      bytes_send += valread;
    } else {
      break;
    }
  }
}

void clientSocket::recvMsg(std::string &msg) {
  while (true) {
    char r;
    int valrecv = recv(this->fd,
                       &r,
                       1,
                       0);
    if (r == '\n')
      break;
    if (valrecv == -1) {
      std::cout << "socketSend: \n" << strerror(errno) << std::endl;
      shutdown(this->fd, SHUT_RDWR);
      throw clientSocketException("socketSend: " + (std::string) strerror(errno));
    }
    if (valrecv == 0) {
      throw clientSocketException("SERVER CLOSED");
    }
    msg += r;
  }
}

clientSocket::~clientSocket() {
  if (this->fd != -1) {
    close(this->fd);
  }
}
