#include <iostream>
#include <utility>
#include "serverPassCommand.h"

serverPassCommand::serverPassCommand(serverUserAuthentication &user_authentication,
                                     serverCfgMap &cfg_map, std::string password) : serverCommand(
    user_authentication,
    cfg_map), password(std::move(password)) {}

std::string serverPassCommand::execute() {
  if ((!this->cfg_map.get("user").compare(this->user_authentication.getUser()))
      && (!this->cfg_map.get("password").compare(password))) {
    this->user_authentication.setState(AUTHENTICATED);
    return "230 " + this->cfg_map.get("loginSuccess") + "\n";
  } else {
    this->user_authentication.setState(NOT_AUTHENTICATED);
    return "530 " + this->cfg_map.get("loginFailed") + "\n";
  }
}

serverPassCommand::~serverPassCommand() {}