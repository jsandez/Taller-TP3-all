#include "serverQuitCommand.h"

serverQuitCommand::serverQuitCommand(serverUserAuthentication &user_authentication, const serverCfgMap &cfg_map) : serverCommand(
    user_authentication, cfg_map) {}

std::string serverQuitCommand::execute() {
  return "221 " + this->cfg_map.get("quitSuccess") + "\n";
}
