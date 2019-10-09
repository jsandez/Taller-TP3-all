#include "serverMkdCommand.h"

#include <utility>

serverMkdCommand::serverMkdCommand(serverUserAuthentication &user_authentication,
                                   serverCfgMap &cfg_map,
                                   serverMonitorDirectory &directory,
                                   std::string dir_name) : serverCommand(
    user_authentication,
    cfg_map), directory(directory), dir_name(std::move(dir_name)) {}

std::string serverMkdCommand::execute() {
  if (!isAuth())
    return unauthMsg();
  else {
    return std::move(directory.addUniq(dir_name));
  }
}

serverMkdCommand::~serverMkdCommand() {}