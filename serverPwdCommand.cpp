#include <iostream>
#include "serverPwdCommand.h"

serverPwdCommand::serverPwdCommand(serverUserAuthentication &user_authentication, const serverCfgMap &cfg_map) : serverCommand(
    user_authentication,
    cfg_map) {}

std::string serverPwdCommand::execute() {
  if (!isAuth())
    return unauthMsg();
  else
    return "257 " + this->cfg_map.get("currentDirectoryMsg") + "\n";
}
