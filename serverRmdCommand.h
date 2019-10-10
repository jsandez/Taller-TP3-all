#ifndef _RMDCOMMAND_H_
#define _RMDCOMMAND_H_
#include "serverCommand.h"

/*
 * Comando para eliminar un archivo
 */
class serverRmdCommand : public serverCommand {
 private:
  serverMonitorDirectory &directory;
  std::string dir_name;
 public:
  serverRmdCommand(serverUserAuthentication &user_authentication,
                   const serverCfgMap &cfg_map,
                   serverMonitorDirectory &directory,
                   std::string dir_name);
  std::string execute() override;
};

#endif
