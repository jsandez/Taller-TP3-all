#ifndef _QUITCOMMAND_H_
#define _QUITCOMMAND_H_
#include "serverCommand.h"

/*
 * Comando para finalizar la conexion del
 * lado del cliente
 */
class serverQuitCommand : public serverCommand {
 public:
  serverQuitCommand(serverUserAuthentication &user_authentication, serverCfgMap &cfg_map);
  std::string execute() override;
  ~serverQuitCommand();
};

#endif
