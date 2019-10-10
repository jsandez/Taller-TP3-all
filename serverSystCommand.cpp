#include "serverSystCommand.h"

serverSystCommand::serverSystCommand(serverUserAuthentication &user_authentication, serverCfgMap &cfg_map) : serverCommand(
        user_authentication, cfg_map) {}

std::string serverSystCommand::execute() {
    if (!isAuth())
        return unauthMsg();
    else
        return "215 " + this->cfg_map.get("systemInfo") + "\n";
}
