#include <iostream>
#include "serverInputFileException.h"
#include "serverSocket.h"
#include "serverMonitorDirectory.h"
#include "serverSocketException.h"
#include "serverAcceptThread.h"

void static __checkArgs(int argc, int expected) {
  if (argc != expected) {
    throw std::runtime_error("ARGUMENTOS INVALIDOS. \nINGRESAR ./server <puerto> <archivo>");
  }
}

int main(int argc, char **argv) {
  try {
    __checkArgs(argc, 3);
    serverDirectory directory;
    serverCfgMap cfg_map(argv[2]);
    serverMonitorDirectory monitor_directory(directory, cfg_map);
    serverSocket srv((std::string) argv[1]);
    serverAcceptThread accept_thread(srv, cfg_map, monitor_directory);
    accept_thread.start();
    char a = 0;
    while (std::cin.get(a)) {
      if (a == 'q')
        break;
    }
    accept_thread.stop();
    srv.shutdownSocket();
    srv.closeSocket();
    accept_thread.join();
  } catch (const serverInputFileException &e) {
    std::cout << e.what() << std::endl;
    return 0;
  } catch (const serverSocketException &e) {
    std::cout << e.what() << std::endl;
    return 0;
  } catch (...) {
    std::cout << "ERROR DESCONOCIDO" << std::endl;
    return 0;
  }
  return 0;
}