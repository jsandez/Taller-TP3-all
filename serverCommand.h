#ifndef TALLER_TP3__SERVERCOMMAND_H_
#define TALLER_TP3__SERVERCOMMAND_H_
#include "serverUserAuthentication.h"
#include "serverCfgMap.h"
#include "serverDirectory.h"
#include "serverMonitorDirectory.h"

/*
 * Clase que representa un comando generico y tambien
 * contiene al factory method que se llamara luego
 * en el servidor cuando se quiera ejecutar un
 * comando.
 */
class serverCommand {
 protected:
  serverUserAuthentication &user_authentication;
  serverCfgMap &cfg_map;

 public:
  serverCommand(serverUserAuthentication &user_authenticacion, serverCfgMap &cfg_map);
  virtual std::string execute() = 0;
  bool isAuth();
  std::string unauthMsg();
  static serverCommand *getCommand(std::string msg,
                                   serverUserAuthentication &user_authentication,
                                   serverCfgMap &cfg_map,
                                   serverMonitorDirectory &directory);
  virtual ~serverCommand();
};

#endif
