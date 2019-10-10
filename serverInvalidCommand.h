#ifndef _INVALIDCOMMAND_H_
#define _INVALIDCOMMAND_H_
#include "serverCommand.h"

/*
 * comando invalido
 */
class serverInvalidCommand : public serverCommand {
 public:
  serverInvalidCommand(serverUserAuthentication &user_authentication, const serverCfgMap &cfg_map);
  std::string execute() override;
};

#endif
