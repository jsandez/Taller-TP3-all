#include "serverWelcomeCommand.h"

serverWelcomeCommand::serverWelcomeCommand(serverUserAuthentication &user_authentication, serverCfgMap &cfg_map)
    : serverCommand(
    user_authentication,
    cfg_map) {}

std::string serverWelcomeCommand::execute() {
  return "220 " + this->cfg_map.get("newClient") + "\n";
}
