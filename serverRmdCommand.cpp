#include "serverRmdCommand.h"

serverRmdCommand::serverRmdCommand(serverUserAuthentication &user_authentication,
                                   const serverCfgMap &cfg_map,
                                   serverMonitorDirectory &directory,
                                   std::string dir_name) : serverCommand(user_authentication, cfg_map),
                                               directory(directory),
                                               dir_name(std::move(dir_name)) {}

std::string serverRmdCommand::execute() {
  if (!isAuth())
    return "530 " + this->cfg_map.get("clientNotLogged") + "\n";
  else {
    return std::move(directory.removeUniq(dir_name));
  }
}
