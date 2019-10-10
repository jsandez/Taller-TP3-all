#include <iostream>
#include "serverAcceptThread.h"
#include "serverSocket.h"
#include "serverSocketException.h"
#include "serverClientThread.h"

serverAcceptThread::serverAcceptThread(serverSocket &socket_server,
                                       serverCfgMap &cfg_map,
                                       serverMonitorDirectory &monitor_directory)
    : socket_server(socket_server),
      cfg_map(cfg_map),
      monitor_directory(monitor_directory) {}

void serverAcceptThread::run() {
  while (1) {
    try {
      serverSocket srvAccept = socket_server.accept();
      serverThread *th = new serverClientThread(srvAccept,
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
    } catch (const serverSocketException &e) {
      std::cout << "SERVER SHUTDOWN" << std::endl;
      break;
    }
  }
}

bool serverAcceptThread::isAlive() {
  return true;
}

void serverAcceptThread::stop() {
  for (serverThread *th: ths) {
    th->stop();
    th->join();
    delete th;
  }
}
