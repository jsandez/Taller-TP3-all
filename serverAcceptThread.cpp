#include <iostream>
#include "serverAcceptThread.h"
#include "serverClientThread.h"
#include "commonSocketException.h"

serverAcceptThread::serverAcceptThread(commonSocket &socket_server,
                                       serverCfgMap &cfg_map,
                                       serverMonitorDirectory &monitor_directory)
    : socket_server(socket_server),
      cfg_map(cfg_map),
      monitor_directory(monitor_directory) {}

void serverAcceptThread::run() {
  while (1) {
    try {
      commonSocket srvAccept = socket_server.accept();
      commonThread *th = new serverClientThread(srvAccept,
                                                cfg_map,
                                                monitor_directory);
      ths.push_back(th);
      th->start();
      auto it = ths.begin();
      while (it != ths.end()) {
        if (!th->isAlive()) {
          th->join();
          delete th;
          it = ths.erase(it);
        } else
          it++;
      }
    } catch (const commonSocketException &e) {
      std::cout << "SERVER SHUTDOWN" << std::endl;
      break;
    }
  }
}

bool serverAcceptThread::isAlive() {
  return true;
}

void serverAcceptThread::stop() {
  for (commonThread *th: ths) {
    th->stop();
    th->join();
    delete th;
  }
  this->socket_server.shutdownSocket();
  this->socket_server.closeSocket();
}
