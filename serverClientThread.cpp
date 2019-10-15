#include "serverClientThread.h"
#include "commonSocketException.h"

serverClientThread::serverClientThread(commonSocket &socket_server,
                                       serverCfgMap &cfg_map,
                                       serverMonitorDirectory &directory)
    : keep_talking(true),
      is_running(true),
      socket_server(std::move(socket_server)),
      ftp_server(cfg_map, directory) {}

void serverClientThread::run() {
  std::string request;
  std::string response;
  while (keep_talking) {
    try {
      request.erase();
      response.erase();
      this->socket_server.recvMsg(request, '\n');
      this->ftp_server.executeCommand(request, response);
      this->socket_server.sendMsg(response);
    }
    catch (const commonSocketException &e) {
      stop();
    }
  }
  this->is_running = false;
}

void serverClientThread::stop() {
  keep_talking = false;
  socket_server.shutdownSocket();
  socket_server.closeSocket();
}

bool serverClientThread::isAlive() {
  return this->is_running;
}
