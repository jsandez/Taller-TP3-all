#include "serverListCommand.h"

serverListCommand::serverListCommand(serverUserAuthentication &user_authentication, serverCfgMap &cfg_map, serverMonitorDirectory &directory)
    : serverCommand(
    user_authentication,
    cfg_map), directory(directory) {}

std::string serverListCommand::execute() {
  if (!isAuth())
    return unauthMsg();
  else {
    std::string msg_return;
    msg_return = msg_return + "150 " + this->cfg_map.get("listBegin") + "\n";
    msg_return = msg_return + std::move(this->directory.getDirectory("drwxrwxrwx 0 1000 1000 4096 Sep 24 12:34"));
    msg_return = msg_return + "226 " + this->cfg_map.get("listEnd") + "\n";
    return std::move(msg_return);
  }
}
