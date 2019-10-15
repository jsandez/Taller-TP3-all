#include <cstring>
#include <iostream>
#include "commonSocket.h"
#include "commonSocketException.h"

void commonSocket::__getAddrInfo(const char *host, std::string service, addrinfo **ai_list) {
  addrinfo hints = {};
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = 0;
  if (host == nullptr) {
    hints.ai_flags = AI_PASSIVE;
  }
  int errcode = getaddrinfo(host, service.c_str(), &hints, ai_list);
  if (errcode != 0) {
    throw commonSocketException("ERROR GETADDRINFO " + (std::string) gai_strerror(errcode));
  }
}

void commonSocket::__bindAddress(addrinfo *ai_list) {
  bool is_bind = false;
  for (addrinfo *ptr = ai_list; ptr != nullptr && !is_bind; ptr = ai_list->ai_next) {
    this->fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    int opt = 1;
    setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (bind(this->fd, ptr->ai_addr, ptr->ai_addrlen) == 0) {
      is_bind = true;
    }
  }
  freeaddrinfo(ai_list);
  if (!is_bind) {
    throw commonSocketException("ERROR HACIENDO BIND");
  }
}

commonSocket::commonSocket(int fd) {
  this->fd = fd;
}

commonSocket::commonSocket() {
  this->fd = -1;
}

void commonSocket::connect(std::string host, const std::string &service) {
  struct addrinfo *ai_list;
  __getAddrInfo(host.c_str(), service, &ai_list);
  bool connected = false;
  for (addrinfo *ptr = ai_list; ptr != NULL && !connected; ptr = ai_list->ai_next) {
    this->fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if (::connect(this->fd, ptr->ai_addr, ptr->ai_addrlen) == 0) {
      connected = true;
    }
  }
  freeaddrinfo(ai_list);
  if (!connected) {
    throw commonSocketException("ERROR CONNECT");
  }
}

void commonSocket::bindAndListen(const std::string &service, int max_waiting_clients) {
  addrinfo *ai_list;
  __getAddrInfo(nullptr, service, &ai_list);
  __bindAddress(ai_list);
  if (listen(this->fd, max_waiting_clients) == -1) {
    throw commonSocketException("ERROR HACIENDO LISTEN");
  }
}

commonSocket commonSocket::accept() {
  int newFd = -1;
  newFd = ::accept(this->fd, NULL, NULL);
  if (newFd == -1) {
    throw commonSocketException("ERROR EN ACCEPT");
  }
  return commonSocket(newFd);
}

void commonSocket::sendMsg(const std::string &msg) {
  size_t bytes_send = 0;
  while (bytes_send < msg.length()) {
    int valread = ::send(this->fd,
                         &msg[bytes_send],
                         msg.length() - bytes_send,
                         MSG_NOSIGNAL);
    if (valread == -1) {
      int error = errno;
      shutdown(this->fd, SHUT_RDWR);
      throw commonSocketException("commonSocket: " + (std::string) strerror(error));
    }
    if (valread > 0) {
      bytes_send += valread;
    } else {
      throw commonSocketException("SOCKET CLOSED");
    }
  }
}

void commonSocket::recvMsg(std::string &msg, const char &delimiter) {
  while (true) {
    char r;
    int valrecv = recv(this->fd,
                       &r,
                       1,
                       0);
    if (r == delimiter)
      break;
    if (valrecv == -1) {
      int error = errno;
      shutdown(this->fd, SHUT_RDWR);
      throw commonSocketException("commonSocket: " + (std::string) strerror(error));
    }
    if (valrecv == 0) {
      throw commonSocketException("SOCKET CLOSED");
    } else
      msg += r;
  }
}

void commonSocket::shutdownSocket() {
  shutdown(this->fd, SHUT_RDWR);
}

void commonSocket::closeSocket() {
  close(this->fd);
  this->fd = -1;
}

commonSocket::~commonSocket() {
  if (this->fd != -1) {
    close(this->fd);
  }
}

commonSocket::commonSocket(commonSocket &&other) {
  this->fd = other.fd;
  other.fd = -1;
}

commonSocket &commonSocket::operator=(commonSocket &&other) {
  if (this == &other) {
    return *this;
  }
  this->fd = other.fd;
  other.fd = -1;
  return *this;
}


