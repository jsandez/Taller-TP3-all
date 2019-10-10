#include "serverHelpCommand.h"

serverHelpCommand::serverHelpCommand(serverUserAuthentication &user_authentication, const serverCfgMap &cfg_map) : serverCommand(
    user_authentication, cfg_map) {}

std::string serverHelpCommand::execute() {
  if (!isAuth())
    return unauthMsg();
  else
    return "214 " + this->cfg_map.get("commands") + "\n";
}
