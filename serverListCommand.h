#ifndef _LISTCOMMAND_H_
#define _LISTCOMMAND_H_

/*
 * Comando que lista el directorio
 */
#include "serverCommand.h"
class serverListCommand : public serverCommand {
 private:
  serverMonitorDirectory &directory;
 public:
  serverListCommand(serverUserAuthentication &user_authentication, const serverCfgMap &cfg_map, serverMonitorDirectory &directory);
  std::string execute() override;
};

#endif
