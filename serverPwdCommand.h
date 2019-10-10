#ifndef _PWDCOMMAND_H_
#define _PWDCOMMAND_H_
#include "serverUserAuthentication.h"
#include "serverCfgMap.h"
#include "serverCommand.h"

/*
 * Comando pwd para saber donde estamos parados
 */
class serverPwdCommand : public serverCommand {
 public:
  serverPwdCommand(serverUserAuthentication &user_authentication, serverCfgMap &cfg_map);
  std::string execute() override;
};

#endif
