#include "serverInvalidCommand.h"

serverInvalidCommand::serverInvalidCommand(serverUserAuthentication &user_authentication, const serverCfgMap &cfg_map)
    : serverCommand(user_authentication, cfg_map) {}

std::string serverInvalidCommand::execute() {
  return "530 " + this->cfg_map.get("unknownCommand") + "\n";
}
