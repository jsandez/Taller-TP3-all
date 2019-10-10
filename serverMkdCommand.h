#ifndef _MKDCOMMAND_H_
#define _MKDCOMMAND_H_
#include "serverCommand.h"

/*
 * Comando que crea un archivo
 */
class serverMkdCommand : public serverCommand {
 private:
  serverMonitorDirectory &directory;
  std::string dir_name;
 public:
  serverMkdCommand(serverUserAuthentication &user_authentication, const serverCfgMap &cfg_map, serverMonitorDirectory &directory, std::string dir_name);
  std::string execute() override;
};

#endif
