#include <iostream>
#include <utility>
#include "serverUserCommand.h"

serverUserCommand::serverUserCommand(serverUserAuthentication &user_authentication,
                                     const serverCfgMap &cfg_map,
                                     std::string user_name) : serverCommand(
    user_authentication,
    cfg_map), user_name(std::move(user_name)) {}

std::string serverUserCommand::execute() {
  this->user_authentication.user(this->user_name);
  this->user_authentication.setState(LOGIN_PROVIDED);
  return "331 " + this->cfg_map.get("passRequired") + "\n";
}
