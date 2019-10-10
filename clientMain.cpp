#include <iostream>
#include "clientSocket.h"
#include "clientSocketException.h"

void static __checkListCommand(std::string &response, clientSocket &client) {
  if (!response.compare(0, 3, "150")) {
    while (response.compare(0, 3, "226")) {
      response.erase();
      client.recvMsg(response);
      std::cout << response << std::endl;
    }
  }
}

int main(int argc, char **argv) {
  try {
    if (argc != 3) {
      throw std::runtime_error("ARGUMENTOS INVALIDOS. \nINGRESAR ./client <host> <puerto>");
    }
    clientSocket client(argv[1], argv[2]);
    client.sendMsg("WELCOME\n");
    std::string msg;
    std::string response;
    client.recvMsg(response);
    std::cout << response << std::endl;
    while (true) {
      msg.erase();
      response.erase();
      std::getline(std::cin, msg);
      if (!std::cin) {
        break;
      }
      client.sendMsg(msg + "\n");
      client.recvMsg(response);
      std::cout << response << std::endl;
      __checkListCommand(response, client);
      if (!response.compare(0, 3, "221")) {
        break;
      }
    }
  } catch (const clientSocketException &e) {
    std::cout << e.what() << std::endl;
    return 0;
  } catch (...) {
    std::cout << "ERROR DESCONOCIDO" << std::endl;
    return 0;
  }
  return 0;
}