#include <iostream>
#include <cstring>
#include "commonSocket.h"
#include "commonSocketException.h"

void static __checkListCommand(std::string &response, commonSocket &client) {
  if (!response.compare(0, 3, "150")) {
    while (response.compare(0, 3, "226")) {
      response.erase();
      client.recvMsg(response, '\n');
      std::cout << response << std::endl;
    }
  }
}

int main(int argc, char **argv) {
  try {
    if (argc != 3) {
      throw std::runtime_error("ARGUMENTOS INVALIDOS. \nINGRESAR ./client <host> <puerto>");
    }
    commonSocket client_socket;
    client_socket.connect(argv[1], argv[2]);
    client_socket.sendMsg("WELCOME\n");
    std::string msg;
    std::string response;
    client_socket.recvMsg(response, '\n');
    std::cout << response << std::endl;
    while (true) {
      msg.erase();
      response.erase();
      std::getline(std::cin, msg);
      if (!std::cin) {
        break;
      }
      client_socket.sendMsg(msg + "\n");
      client_socket.recvMsg(response, '\n');
      std::cout << response << std::endl;
      __checkListCommand(response, client_socket);
      if (!response.compare(0, 3, "221")) {
        break;
      }
    }
    client_socket.shutdownSocket();
  } catch (const commonSocketException &e) {
    if (strncmp(e.what(), "SOCKET CLOSED", 13) == 0) {
      std::cout << "SERVER SHUTDOWN" << std::endl;
    } else {
      std::cout << e.what() << std::endl;
    }
    return 0;
  } catch (...) {
    std::cout << "ERROR DESCONOCIDO" << std::endl;
    return 0;
  }
  return 0;
}