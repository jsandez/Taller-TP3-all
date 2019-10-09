#ifndef _FTPCOMMANDS_H_
#define _FTPCOMMANDS_H_
#include <set>
#include "serverCfgMap.h"
#include "serverDirectory.h"
#include "serverUserAuthentication.h"
#include "serverCommand.h"
#include "serverMonitorDirectory.h"

/*
 * Clase que representa al servidor
 * al cual el cliente le realizara todas
 * sus peticiones. Esto solamente supone
 * una plantilla en la cual lo que cambia
 * son los recursos, en este caso directory
 * Lo demas sirve como interfaz para mostrar
 * los comandos de cfg_map
 */
class serverFTPServer {
 private:
  serverCfgMap &cfg_map;
  serverMonitorDirectory &directory;
  serverUserAuthentication user_authentication;

 public:
  serverFTPServer(serverCfgMap &cfg_map, serverMonitorDirectory &directory);
  void executeCommand(std::string msg, std::string &response);
};

#endif
