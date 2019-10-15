#include <iostream>
#include "serverInputFileException.h"
#include "commonSocket.h"
#include "serverMonitorDirectory.h"
#include "serverAcceptThread.h"
#include "commonSocketException.h"

int main(int argc, char **argv) {
  try {
    if (argc != 3) {
      throw std::runtime_error("ARGUMENTOS INVALIDOS. \nINGRESAR ./server <puerto> <archivo>");
    }
    serverDirectory directory;
    std::ifstream input_file_stream(argv[2]);
    if (input_file_stream.fail()) {
      throw serverInputFileException("FALLO AL ABRIR EL ARCHIVO");
    }
    serverCfgMap cfg_map(input_file_stream);
    serverMonitorDirectory monitor_directory(directory, cfg_map);
    commonSocket socket_server;
    socket_server.bindAndListen((std::string) argv[1], 20);
    serverAcceptThread accept_thread(socket_server, cfg_map, monitor_directory);
    accept_thread.start();
    char a = 0;
    while (std::cin.get(a)) {
      if (a == 'q')
        break;
    }
    accept_thread.stop();
    accept_thread.join();
  } catch (const serverInputFileException &e) {
    std::cout << e.what() << std::endl;
    return 0;
  } catch (const commonSocketException &e) {
    std::cout << e.what() << std::endl;
    return 0;
  } catch (...) {
    std::cout << "ERROR DESCONOCIDO" << std::endl;
    return 0;
  }
  return 0;
}