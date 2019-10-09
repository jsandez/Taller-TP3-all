#ifndef _WELCOME_H_
#define _WELCOME_H_
#include "serverCommand.h"

/*
 * Comando de bienvenida
 */
class serverWelcomeCommand : public serverCommand {
 public:
  serverWelcomeCommand(serverUserAuthentication &user_authentication, serverCfgMap &cfg_map);
  std::string execute() override;
  ~serverWelcomeCommand();
};

#endif
