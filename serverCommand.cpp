#include "serverCommand.h"
#include "serverPassCommand.h"
#include "serverWelcomeCommand.h"
#include "serverUserCommand.h"
#include "serverPwdCommand.h"
#include "serverMkdCommand.h"
#include "serverRmdCommand.h"
#include "serverListCommand.h"
#include "serverSystCommand.h"
#include "serverHelpCommand.h"
#include "serverQuitCommand.h"
#include "serverInvalidCommand.h"

serverCommand::serverCommand(serverUserAuthentication &user_authentication, serverCfgMap &cfg_map)
    : user_authentication(user_authentication), cfg_map(cfg_map) {}

/*
* Metodo que se encarga en tiempo de ejecucion
 * de elegir el comando que se debe ejeutar basandose
 * en la linea ingresada por parametro
*/
serverCommand *serverCommand::getCommand(std::string msg,
                                         serverUserAuthentication &user_authentication,
                                         serverCfgMap &cfg_map,
                                         serverMonitorDirectory &directory) {
  if (!msg.compare("WELCOME"))
    return new serverWelcomeCommand(user_authentication, cfg_map);
  else if (!msg.compare(0, 5, "USER "))
    return new serverUserCommand(user_authentication, cfg_map, msg.substr(5));
  else if (!msg.compare(0, 5, "PASS "))
    return new serverPassCommand(user_authentication, cfg_map, msg.substr(5));
  else if (!msg.compare("PWD"))
    return new serverPwdCommand(user_authentication, cfg_map);
  else if (!msg.compare("LIST"))
    return new serverListCommand(user_authentication, cfg_map, directory);
  else if (!msg.compare(0, 4, "MKD "))
    return new serverMkdCommand(user_authentication, cfg_map, directory,
                                msg.substr(4));
  else if (!msg.compare(0, 4, "RMD "))
    return new serverRmdCommand(user_authentication, cfg_map, directory,
                                msg.substr(4));
  else if (!msg.compare("SYST"))
    return new serverSystCommand(user_authentication, cfg_map);
  else if (!msg.compare("HELP"))
    return new serverHelpCommand(user_authentication, cfg_map);
  else if (!msg.compare("QUIT"))
    return new serverQuitCommand(user_authentication, cfg_map);
  else
    return new serverInvalidCommand(user_authentication, cfg_map);
}

bool serverCommand::isAuth() {
  return (this->user_authentication.checkState(AUTHENTICATED));
}

std::string serverCommand::unauthMsg() {
  return "530 " + this->cfg_map.get("clientNotLogged") + "\n";
}

serverCommand::~serverCommand() {}
