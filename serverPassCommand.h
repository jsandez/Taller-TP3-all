#ifndef _PASSCOMMAND_H_
#define _PASSCOMMAND_H_
#include "serverCommand.h"

/*
 * Comando para ingresar la password
 */
class serverPassCommand : public serverCommand {
 private:
  std::string password;
 public:
  serverPassCommand(serverUserAuthentication &user_authentication,
                    serverCfgMap &cfg_map, std::string password);
  std::string execute() override;
};

#endif
