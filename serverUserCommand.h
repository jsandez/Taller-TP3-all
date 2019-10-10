#ifndef _USERCOMMAND_H_
#define _USERCOMMAND_H_
#include "serverCommand.h"

/*
 * Comando para ingresar el user_name
 */
class serverUserCommand : public serverCommand {
 private:
  std::string user_name;
 public:
  serverUserCommand(serverUserAuthentication &user_authenticacion, const serverCfgMap &cfg_map, std::string user_name);
  std::string execute() override;
};

#endif
