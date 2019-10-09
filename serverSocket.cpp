#include <cstring>
#include <stdexcept>
#include <iostream>
#include "serverSocket.h"
#include "serverSocketException.h"

void serverSocket::__getSrvAddrInfo(std::string service, addrinfo **ai_list) {
  addrinfo hints = {};
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  int errcode = getaddrinfo(nullptr, service.c_str(), &hints, ai_list);
  if (errcode != 0) {
    freeaddrinfo(*ai_list);
    throw serverSocketException("ERROR GETADDRINFO " + (std::string) gai_strerror(errcode));
  }
}

void serverSocket::__bindAddress(addrinfo *ai_list) {
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
    close(this->fd);
    throw serverSocketException("ERROR HACIENDO BIND");
  }
}

serverSocket::serverSocket(int fd) {
  this->fd = fd;
}

serverSocket::serverSocket(const std::string service) {
  addrinfo *ai_list;
  __getSrvAddrInfo(service, &ai_list);
  __bindAddress(ai_list);
  if (listen(this->fd, 20) == -1) {
    close(this->fd);
    throw serverSocketException("ERROR HACIENDO LISTEN");
  }
}

serverSocket serverSocket::accept() {
  int newFd = -1;
  newFd = ::accept(this->fd, NULL, NULL);
  if (newFd == -1) {
    throw serverSocketException("ERROR EN ACCEPT");
  }
  int opt = 1;
  setsockopt(newFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  return serverSocket(newFd);
}

void serverSocket::sendMsg(const std::string msg) {
  size_t bytes_send = 0;
  while (bytes_send < msg.length()) {
    int valread = ::send(this->fd,
                         &msg[bytes_send],
                         msg.length() - bytes_send,
                         MSG_NOSIGNAL);
    if (valread == -1) {
      std::cout << "socketSend: \n" << strerror(errno) << std::endl;
      shutdown(this->fd, SHUT_RDWR);
      throw serverSocketException("socketSend: " + (std::string) strerror(errno));
    }
    if (valread > 0) {
      bytes_send += valread;
    } else {
      break;
    }
  }
}

void serverSocket::recvMsg(std::string &msg) {
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
      throw serverSocketException("socketSend: " + (std::string) strerror(errno));
    }
    if (valrecv == 0) {
      throw serverSocketException("CLIENT CLOSED");
    } else
      msg += r;
  }
}

serverSocket::serverSocket(serverSocket &&other) {
  this->fd = other.fd;
  other.fd = -1;
}

serverSocket &serverSocket::operator=(serverSocket &&other) {
  if (this == &other) {
    return *this;
  }
  this->fd = other.fd;
  other.fd = -1;
  return *this;
}

void serverSocket::shutdownSocket() {
  shutdown(this->fd, SHUT_RDWR);
}

void serverSocket::closeSocket() {
  close(this->fd);
}

serverSocket::~serverSocket() {}
